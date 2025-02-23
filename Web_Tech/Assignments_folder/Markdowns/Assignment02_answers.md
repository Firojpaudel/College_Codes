## Assignment 02 Question & Answers:

#### Qn 1. What is CSS Media Query? Show the use of maxwidth & minwidth properties.

***Answer***:
CSS Media Queries are a feature of CSS3 that allow developers to apply specific styles based on the characteristics of the device or browser, such as screen size, resolution, or orientation. They enable responsive web design by adapting layouts and styles to different devices, ensuring an optimal user experience across various screen sizes.

**`max-width` and `min-width` Properties**
- `max-width`: Applies styles when the viewport width is less than or equal to the specified value. It is commonly used for targeting smaller screens like mobile devices.

- `min-width`: Applies styles when the viewport width is greater than or equal to the specified value. It is often used for larger screens like tablets or desktops.

*Example Code*:

Here is a practical example demonstrating the use of max-width and min-width:

```css
/* Default styles */
body {
  background-color: white;
  font-size: 16px;
}

/* Styles for screens smaller than or equal to 600px */
@media only screen and (max-width: 600px) {
  body {
    background-color: lightblue;
    font-size: 14px;
  }
}

/* Styles for screens larger than or equal to 768px */
@media only screen and (min-width: 768px) {
  body {
    background-color: lightgreen;
    font-size: 18px;
  }
}

/* Styles for screens between 600px and 768px */
@media only screen and (min-width: 600px) and (max-width: 768px) {
  body {
    background-color: lightcoral;
    font-size: 16px;
  }
}
```
**Explanation**:

- The default styles apply to all devices unless overridden by a media query.

- The `max-width` query targets devices with a width of $600$ px or less, applying a light blue background and smaller font size.

- The min-width query targets devices with a width of $768$ px or more, applying a light green background and larger font size.

- A combined query with both min-width and max-width defines styles specifically for devices between $600$ px and $768$ px, applying a light coral background.

#### Qn 2. List the properties associated with 2D effects and transformation. Show examples.

***Answer:***

**Properties Associated with 2D Effects and Transformations**

The CSS `transform` property allows you to apply various 2D transformations to elements, such as translating, rotating, scaling, skewing, or combining these effects. Below are the key 2D transformation properties and their descriptions:

1. `translate()`
    - Moves an element from its current position.

    - Can be applied along the X-axis, Y-axis, or both using `translateX()`, `translateY()`, or `translate(x, y)`.

        ***Example***:
        ```css
        div {
            transform: translate(50px, 100px); /* Moves element 50px right and 100px down */
        }
        ```

2. `rotate()`
    - Rotates an element around its origin by a specified angle *(in degrees)*.

    - Positive values rotate clockwise; negative values rotate counter-clockwise.

        ***Example:***
        ```css
        div {
            transform: rotate(45deg); /* Rotates element by 45 degrees */
        }
        ```
3. `scale()`
    - Resizes an element by scaling it along the X and Y axes.

    - Use `scaleX()` or `scaleY()` for individual axis scaling.

        ***Example:***
        ```css
        div {
            transform: scale(1.5); /* Increases size by 1.5 times */
        }
        ```
4. `skew()`
    - Skews an element along the X-axis, Y-axis, or both using angles.

    - Use `skewX()` or `skewY()` for individual axis skewing.

        ***Example:***
        ```css
        div {
            transform: skew(30deg, 10deg); /* Skews 30 degrees on X-axis and 10 degrees on Y-axis */
        }
        ```
5. `matrix()`
    - Combines all transformations (translate, rotate, scale, skew) into one function.

    - Takes six parameters: `matrix(scaleX(), skewY(), skewX(), scaleY(), translateX(), translateY())`.

        ***Example:***
        ```css
        div {
            transform: matrix(1, -0.3, 0.3, 1, 50, 100); /* Combines transformations */
        }
        ```
**Examples of Multiple Transformations**

You can combine multiple transformations in a single rule:
```css
div {
  transform: translate(50px, 100px) rotate(45deg) scale(1.5);
}
```
This moves the element by `(50px, 100px)`, rotates it by `45°`, and scales it by `1.5x`.