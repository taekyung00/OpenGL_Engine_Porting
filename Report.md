### 11/23

# # OpenGL 포팅 이슈 리포트: 렌더링 파이프라인 및 텍스트 시스템 수정

## 1. Texture::Draw 수정: Pivot Point 및 행렬 순서

### 1.1 문제 상황 (Problem)

Raylib의 Immediate Mode 렌더링을 OpenGL 커스텀 엔진으로 이식하는 과정에서, `Texture::Draw` 함수의 변환 행렬(Transformation Matrix) 적용 방식에 차이가 발생했습니다.

- **Raylib:** 텍스처의 **좌상단(Top-Left) 모서리**를 기준점(Pivot)으로 회전 및 이동합니다.

- **초기 구현:** 객체의 **중심(Center)**을 기준으로 회전한 뒤 이동하는 방식(`T * M * S`)으로 구현되어, 회전 축이 어긋나는 현상이 발생했습니다.

### 1.2 해결 방안 (Solution)

Raylib과 동일하게 모서리를 기준으로 변환하기 위해 행렬 곱셈 순서를 변경했습니다.

- **기존 순서 (`T * M * S`):** `Translate(Final) * DisplayMatrix * Scale`
  
  - 객체 중심을 기준으로 회전이 적용됨.

- **수정된 순서 (`M * T * S`):** `DisplayMatrix * Translate(PivotOffset) * Scale`
  
  - `DisplayMatrix`(월드 변환)를 적용하기 **전**에, 쿼드의 중심을 이동시켜 (0,0)이 모서리에 오도록 만듭니다.

**수정된 코드 (`source/Engine/Texture.cpp`):**

```
void Texture::Draw(const Math::TransformationMatrix& display_matrix, Math::ivec2 texel_position, Math::ivec2 frame_size, unsigned int color, float depth)
{
    CS200::IRenderer2D* renderer = Engine::GetTextureManager().GetRenderer2D();

    // ... (UV 좌표 계산 로직 생략) ...

    // 쿼드의 중심(-0.5 ~ 0.5)을 (0 ~ 1)로 옮기기 위한 오프셋
    Math::vec2 half_size{ frame_size.x * 0.5, frame_size.y * 0.5 };

    // [중요 수정] TranslationMatrix 위치 변경
    // 순서: Scale(크기설정) -> Translate(중심점 이동) -> DisplayMatrix(월드 배치)
    // 결과: (0,0) 모서리를 기준으로 DisplayMatrix의 회전/이동이 적용됨
    const auto world_transformation = display_matrix * Math::TranslationMatrix(half_size) * Math::ScaleMatrix(frame_size);

    renderer->DrawQuad(world_transformation, textureHandle, texel_coord_bl, texel_coord_tr, color, depth);
}
```

## 2. 파생된 문제: TextManager 렌더링 오류

### 2.1 증상 (Symptom)

`Texture::Draw`를 수정한 직후, 일반적인 스프라이트는 정상적으로 출력되었으나 `TextManager`를 통해 렌더링되는 텍스트들이 화면에서 사라지는 현상이 발생했습니다.

### 2.2 원인 분석 (Root Cause)

`Font::DrawChar` 함수에는 이미지 좌표계(Top-Left Origin)와 OpenGL 좌표계(Bottom-Left Origin)의 차이를 보정하기 위한 **Y축 반전 행렬(`Flip`)**이 존재했습니다.

```
// Font::DrawChar 내부의 레거시 로직
const auto flip = Math::ScaleMatrix(Math::vec2{ 1, -1 }); // Y축을 -1로 뒤집음
```

이 `flip` 행렬이 변경된 `Texture::Draw`의 행렬 순서(`M * T * S`)와 결합되면서 문제가 발생했습니다.

1. **기존 (`T * M * S`):** `Translate(Pivot)`이 **마지막**에 적용되어, `flip`으로 뒤집힌 좌표를 다시 양수 영역으로 끌어올렸습니다.

2. **변경 (`M * T * S`):** `DisplayMatrix` 자리에 들어온 `flip`이 **가장 먼저** 적용되면서, 이후 적용되는 `Translate` 벡터까지 모두 Y축 반전시켜 버렸습니다.

3. **결과:** 글자의 Y좌표가 음수 영역(`0 ~ -Height`)으로 반전되어 뷰포트 밖으로 사라짐 (Clipping).

## 3. 최종 해결: Font 클래스 위치 보정 (Patch)

### 3.1 해결 전략 (Offset Patch)

`Font` 클래스의 기존 로직을 최대한 유지하면서 문제를 해결하기 위해, `Flip`이 적용되기 직전에 강제로 위치를 보정하는 행렬을 추가했습니다.

- **원리:** `Flip`(`Scale(1, -1)`)을 하기 전에 글자의 높이(`Height`)만큼 Y축 양의 방향으로 미리 이동(`Offset`)시켜 놓습니다.

- **결과:** 뒤집혔을 때 음수 영역으로 떨어지는 대신, 정상적인 화면 영역(`0 ~ Height`)에 안착하게 됩니다.

### 3.2 수정된 코드 (`source/Engine/Font.cpp`)

`Font::DrawChar` 함수에 `offset_up` 행렬을 추가하고 곱셈 순서를 조정했습니다.

```
void Font::DrawChar(Math::TransformationMatrix& matrix, char c, CS200::RGBA color)
{
    const Math::irect& display_rect   = GetCharRect(c);
    const Math::ivec2 top_left_texel = { display_rect.Left(), display_rect.Bottom() };

    if (c != ' ')
    {
        // 1. Y축 반전 행렬 (기존)
        const auto flip = Math::ScaleMatrix(Math::vec2{ 1, -1 });

        // 2. [Patch] 높이만큼 위로 올려주는 오프셋 행렬 생성
        // Flip으로 인해 음수 좌표로 내려갈 것을 대비하여 미리 위로 올림
        const auto offset_up = Math::TranslationMatrix(Math::vec2{ 0.0, static_cast<double>(display_rect.Size().y) });

        // 3. 순서: Matrix(World) * Offset(Local Up) * Flip(Local Invert)
        // 새로운 Texture::Draw 로직(M*T*S) 하에서도 정상 위치(양수 Y)에 그려짐
        texture.Draw(matrix * offset_up * flip, top_left_texel, display_rect.Size(), color);
    }

    // 다음 글자 위치로 이동
    matrix *= Math::TranslationMatrix(Math::ivec2{ display_rect.Size().x, 0 });
}
```

### 3.3 결과

- `Texture::Draw`는 Raylib과 동일한 Pivot(Corner) 기준 변환을 수행합니다.

- `TextManager`는 추가된 Offset 행렬 덕분에 올바른 위치에 텍스트를 렌더링합니다.
