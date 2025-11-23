### 11/23

# TextManager 렌더링 문제 분석 및 해결 리포트

## 1. 문제 상황 (Problem)

**증상:** Raylib 스타일의 렌더링 로직을 OpenGL로 이식하는 과정에서, `Texture::Draw`의 행렬 연산 순서를 변경(`Pivot` 보정)한 직후 텍스트(Font)가 화면에서 사라지는 현상이 발생함.

**배경:**

- **기존 (`T * M * S`):** Raylib은 Top-Left를 (0,0)으로 사용하며, 텍스처를 그릴 때 크기(Scale) -> 변환(Matrix) -> 중심점 이동(Translate) 순서로 연산했습니다.

- **변경 (`M * T * S`):** 정확한 회전 축(Pivot) 처리를 위해, 크기(Scale) -> 중심점 이동(Translate) -> 변환(Matrix) 순서로 변경했습니다.

## 2. 원인 분석 (Root Cause)

`Font::DrawChar` 함수에는 이미지 좌표계(Top-Left)와 OpenGL 좌표계(Bottom-Left)의 차이를 보정하기 위한 **Y축 반전 행렬(`Flip`)**이 존재했습니다.

```
// 기존 Font::DrawChar 내부
const auto flip = Math::ScaleMatrix(Math::vec2{ 1, -1 }); // Y축을 -1로 뒤집음
texture.Draw(matrix * flip, ...);
```

이 `flip` 행렬이 변경된 `Texture::Draw` 로직과 결합되면서 다음과 같은 문제가 발생했습니다.

1. **기존 순서 (`T * M * S`):**
   
   - `Translate(Pivot)`이 **가장 마지막**에 적용되었습니다.
   
   - `matrix * flip`으로 인해 Y축이 뒤집히더라도, 마지막에 `Pivot` 오프셋이 더해지면서 글자가 화면(양수 좌표)으로 올라왔습니다.

2. **새로운 순서 (`M * T * S`):**
   
   - `DisplayMatrix`(`matrix * flip`)가 **가장 먼저** 적용됩니다.
   
   - 이후 `Translate(Pivot)`이 적용되지만, 이미 `flip`에 의해 전체 좌표계가 뒤집힌 상태입니다.
   
   - 결과적으로 글자의 위치(Y좌표)가 **음수 영역(0 ~ -Height)**으로 반전되어 뷰포트 밖으로 사라졌습니다.

## 3. 해결 솔루션: 위치 보정 (Offset Patch)

기존 `Font` 클래스의 로직을 크게 건드리지 않고, 사라진 글자를 화면 위로 끌어올리는 **보정 행렬(`offset_up`)**을 추가하여 해결합니다.

### 수정 원리

`Flip` 행렬(`Scale(1, -1)`)을 적용하기 직전에, 글자의 높이(`Height`)만큼 Y축 양의 방향으로 이동시키는 `Translation`을 먼저 적용합니다.

- **수식:** `Matrix * Offset_Up * Flip`

- **결과:** (0 ~ Height) 영역의 이미지가 `Offset_Up`에 의해 (0 ~ 2*Height)로 이동하고 싶어하지만, 바로 뒤의 `Flip`에 의해 (0 ~ -Height)로 뒤집히는 대신 **(0 ~ Height)** 범위, 즉 정상적인 화면 영역에 안착하게 됩니다.

## 4. 수정된 코드 (source/Engine/Font.cpp)

`Font::DrawChar` 함수 내부만 수정합니다.

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
        // Flip으로 인해 음수 좌표로 내려간 글자를 다시 위로 보정함
        const auto offset_up = Math::TranslationMatrix(Math::vec2{ 0.0, static_cast<double>(display_rect.Size().y) });

        // 3. 순서: Matrix(World) * Offset(Local Up) * Flip(Local Invert)
        // 새로운 Texture::Draw 로직(M*T*S)에서도 정상 위치에 그려지게 됨
        texture.Draw(matrix * offset_up * flip, top_left_texel, display_rect.Size(), color);
    }
    matrix *= Math::TranslationMatrix(Math::ivec2{ display_rect.Size().x, 0 });
}
```
