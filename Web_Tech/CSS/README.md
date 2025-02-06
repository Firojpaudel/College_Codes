## CSS Notes 

**CSS**: Cascading Style Sheet ; Design Element 

### Inline CSS

Inline CSS is used to apply a unique style to a single HTML element. It is added directly within the HTML tag using the `style` attribute. This method is useful for quick styling changes or when you need to override other CSS rules.

#### Syntax
```html
<tagname style="property:value;">
```

#### Example
```html
<p style="color: blue; font-size: 20px;">This is a paragraph with inline CSS.</p>
```

#### Advantages
- Quick and easy to apply.
- Useful for testing and debugging.
- Overrides external and internal CSS.

#### Disadvantages
- Not suitable for large projects.
- Reduces code maintainability.
- Increases HTML file size.

#### Best Practices
- Use sparingly for small changes.
- Prefer external or internal CSS for better maintainability.
- Avoid using inline CSS for large-scale styling.

Inline CSS is a powerful tool but should be used judiciously to maintain clean and efficient code.

### External CSS

External CSS is used to apply styles to multiple HTML pages from a single CSS file. This method is ideal for large projects as it helps maintain consistency and reduces code duplication.

#### Syntax
To link an external CSS file, use the `<link>` tag within the `<head>` section of your HTML document:
```html
<head>
    <link rel="stylesheet" type="text/css" href="styles.css">
</head>
```

#### Example
HTML file:
```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="styles.css">
    <title>External CSS Example</title>
</head>
<body>
    <h1>This is a heading</h1>
    <p>This is a paragraph.</p>
</body>
</html>
```

CSS file (`styles.css` but used as [`day04.css`](./day04.css) here to make it more readable 🥴):
```css
h1 {
    color: green;
    font-size: 24px;
}

p {
    color: blue;
    font-size: 16px;
}
```

#### Advantages
- Keeps HTML and CSS code separate, improving readability.
- Allows for reusability across multiple HTML files.
- Easier to maintain and update styles.

#### Disadvantages
- Requires an additional HTTP request to load the CSS file.
- Changes in the CSS file affect all linked HTML files.

#### Best Practices
- Use descriptive class and ID names.
- Organize CSS rules logically (e.g., by section or component).
- Minimize the use of `!important` to avoid specificity issues.

External CSS is a robust and scalable solution for styling web pages, especially in larger projects.
