# 12 filters by code

## An image processing (or photo editing) software like Photo Shop allows you to load an image and apply some filters to image and then save it again.

> ### Original Image
![image](https://user-images.githubusercontent.com/101745968/162193736-754981e5-e992-4f50-b3f0-6890e0cdce86.png)


> ### Filter 1: Black and White Image
![image](https://user-images.githubusercontent.com/101745968/162193785-7015938f-40f5-4692-b8d9-c5e196c89a63.png)


<details><summary>show details</summary>
<p>

      If you apply this function to the loaded image, it will produce another version of the image that is black and white.

</p>
 
```
  fist we convert the RGB image to gray image
  get black and white by calculating the average gray level for all pixels in the  image
  And then every pixel above the average is turned to white (255)  and every pixel below average is turned to black (0).
```
 
</details>
 
> ### Filter 2: Invert Image
![image](https://user-images.githubusercontent.com/101745968/162194119-7eba2ec8-667d-445c-88eb-2874922cee0c.png)

<details><summary>show details</summary>
<p>

      If you apply this function to the loaded image, it will produce the negative 
      of the image and you can store it in the file name you give.

</p>
 
 ```
  it convert every pixel to its negation value (255 - value)
 ```
 
</details>


> ### Filter 3: Merge Images
![image](https://user-images.githubusercontent.com/101745968/162194286-0d62941a-15c1-48dc-8b56-1b3e65e7f19a.png)
<details><summary>show details</summary>
<p>

      In this function, you will be asked to enter the name of another image, then the program will load this image. 

</p>
 
 ```
      The program will create a new image, with every pixel equal the average each RGB level value
      of the corresponding pixels in the images to merge.
```
 
</details>

> ### Filter 4: Flip Image
![image](https://user-images.githubusercontent.com/101745968/162194352-4401fd3f-4a35-45fd-ac17-f413a8a41a5b.png)
![image](https://user-images.githubusercontent.com/101745968/162194374-e7b91ca5-0f35-4b22-a109-02376a4b3519.png)
<details><summary>show details</summary>
<p>

      This filter allows the user to flip the image horizontally or vertically, as if it is reflected on a mirror

</p>
 
</details>


> ### Filter 5: Darken and Lighten Image
![image](https://user-images.githubusercontent.com/101745968/162194853-47ce02c0-e24d-4eb1-a4b0-434f97945a0d.png)
![image](https://user-images.githubusercontent.com/101745968/162194886-5a1a0b99-ffc7-41c1-960e-a2de0c5b3400.png)

<details><summary>show details</summary>
<p>

      This filter allows the user to make the image darker or lighter by 50%

</p>
 
</details>

> ### Filter 6: Rotate Image
![image](https://user-images.githubusercontent.com/101745968/162195224-767c4428-9be5-4c7d-b12c-5dcb32791c33.png)
![image](https://user-images.githubusercontent.com/101745968/162195252-45efcae3-5b4f-41a1-81d4-0c70f2392a0e.png)
![image](https://user-images.githubusercontent.com/101745968/162195282-437c4138-3c1b-4d62-a383-863d834785e3.png)

<details><summary>show details</summary>
<p>

      This filter allows the user to rotate the image clockwise by 90º, 180º or 270º as the user chooses.

</p>
 
</details>

> ### Filter 7: Detect Image Edges
![image](https://user-images.githubusercontent.com/101745968/162195444-8e293388-11b7-480a-a445-7ed115f1389d.png)
<details><summary>show details</summary>
<p>

      This function finds the edges of the drawings in the image and turns the image into a skeleton version
      of the original as if it is drawn with pencil without coloring as shown. 

</p>
 
</details>

> ### Filter 8: Enlarge Image
![image](https://user-images.githubusercontent.com/101745968/162195755-6f913d44-784c-4cdd-a7ea-909d0ce56ea7.png)
![image](https://user-images.githubusercontent.com/101745968/162195781-43d46a87-0134-46c1-8ab5-e9340413b904.png)

![image](https://user-images.githubusercontent.com/101745968/162195809-c044ca95-57a6-4af6-b61f-77ba6edc38d0.png)
![image](https://user-images.githubusercontent.com/101745968/162195831-b76936a4-a768-4dcf-831a-4f2faa762c0f.png)

<details><summary>show details</summary>
<p>

      This filter allows the user to enlarge one of the four quarters of the image into a separate new image.

</p>
 
</details>

> ### Filter 9: Shrink Image
![image](https://user-images.githubusercontent.com/101745968/162196278-ae9287ba-164c-43e8-a48e-9e4187a3316c.png)
![image](https://user-images.githubusercontent.com/101745968/162196317-9567fde6-e65c-4a86-b68f-bf2f6150d8e1.png)
![image](https://user-images.githubusercontent.com/101745968/162196340-a7bee054-cf30-4f5d-a3dc-648772c4a63f.png)

<details><summary>show details</summary>
<p>

      This filter allows the user to shrink the image dimensions to 1/2, 1/3 or 1/4 the original dimensions.

</p>
 
</details>

> ### Filter a: Mirror Image
![image](https://user-images.githubusercontent.com/101745968/162196798-b38f32e1-8199-484c-b38a-974f0bb58f93.png)
![image](https://user-images.githubusercontent.com/101745968/162196838-ca05ff24-6bd6-4a31-9103-41c9267de8b6.png)

![image](https://user-images.githubusercontent.com/101745968/162196859-f71f9c6d-9f50-447d-8315-33f6d083b5e5.png)
![image](https://user-images.githubusercontent.com/101745968/162196895-0ecf9d37-ed2f-4e00-b180-50af6928059f.png)

<details><summary>show details</summary>
<p>

      This filter mirrors 1/2 of the image as seen here in order: Left 1/2, Right 1/2, Upper 1/2 and Lower 1/2.

</p>
 
</details>

> ### Filter b: Shuffle Image
![image](https://user-images.githubusercontent.com/101745968/162197195-7fef89b8-b1b9-4601-812e-8a94ffac03a0.png)
![image](https://user-images.githubusercontent.com/101745968/162197275-689610cf-4d09-4434-8e9f-c5c126ca0ae2.png)

<details><summary>show details</summary>
<p>

      Assume the image consist of 4 quarters as shown
      the user enters the order he wants to the quarters in the new image. Wrong input is rejected.

</p>
 
```
  Assume he entered 4 3 2 1 he gets left image. Or if he enters 3 1 4 2 he gets right image. User can enter any order he likes.
```
 
</details>

> ### Filter c: Blur Image
![image](https://user-images.githubusercontent.com/101745968/162197377-47419044-7ef5-4a25-bf7c-93274b7a0ff6.png)
<details><summary>show details</summary>
<p>

      This filter produces a blur version of the image.

</p>
 
</details>
