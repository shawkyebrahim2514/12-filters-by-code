# 12 filters by code

## An image processing (or photo editing) software like Photo Shop allows you to load an image and apply some filters to image and then save it again.

> ### Original Image
![image](https://user-images.githubusercontent.com/101745968/161277494-8f3b4ec6-9135-44d4-a2a4-c5b8ffe10b05.png)

> ### Filter 1: Black and White Image
![image](https://user-images.githubusercontent.com/101745968/161271458-6f95c132-3795-4e05-838a-a328552d9c56.png)

<details><summary>show details</summary>
<p>

      If you apply this function to the loaded image, it will produce another version of the image that is black and white.

</p>
 
```
You can do this by calculating the average gray level for all pixels in the  image
And then every pixel above the average is turned to white (255)  and every pixel below average is turned to black (0).
```
 
</details>
 
> ### Filter 2: Invert Image
![image](https://user-images.githubusercontent.com/101745968/161272326-9c2f5aae-ca41-4e1b-bc0f-7942c2a8428e.png)
<details><summary>show details</summary>
<p>

      If you apply this function to the loaded image, it will produce the negative 
      of the image and you can store it in the file name you give.

</p>
 
 ```
     The negative has every black pixel turned to white and every white pixel turned to black
     and every gray pixel is turned to opposite level of brightness (255 – pixel value)
```
 
</details>

> ### Filter 1: Black and White Image
![image](https://user-images.githubusercontent.com/101745968/161271458-6f95c132-3795-4e05-838a-a328552d9c56.png)

<details><summary>show details</summary>
<p>

      If you apply this function to the loaded image, it will produce another version of the image that is black and white.

</p>
 
```
     You can do this by calculating the average gray level for all pixels in the  image
     And then every pixel above the average is turned to white (255)  and every pixel below average is turned to black (0).
```
 
</details>
 
> ### Filter 3: Merge Images
![image](https://user-images.githubusercontent.com/101745968/161274150-cc2271e5-ebed-4d92-80fe-5bb1befb9792.png)
<details><summary>show details</summary>
<p>

      In this function, you will be asked to enter the name of another image, then the program will load this image. 

</p>
 
 ```
      The program will create a new image, with every pixel equal the average gray level
      of the corresponding pixels in the images to merge.
```
 
</details>

> ### Filter 4: Flip Image
![image](https://user-images.githubusercontent.com/101745968/161274588-2caff2a0-c0a5-4a30-9eb6-c020ab9f6d39.png)
<details><summary>show details</summary>
<p>

      This filter allows the user to flip the image horizontally or vertically, as if it is reflected on a mirror

</p>
 
</details>

> ### Filter 5: Rotate Image
![image](https://user-images.githubusercontent.com/101745968/161274905-2af39359-998e-4553-9c5e-8f4b3ed93718.png)
<details><summary>show details</summary>
<p>

      This filter allows the user to rotate the image clockwise by 90º, 180º or 270º as the user chooses.

</p>
 
</details>

> ### Filter 6: Darken and Lighten Image
![image](https://user-images.githubusercontent.com/101745968/161275272-36859930-d2f9-412d-b97c-53d273c8248c.png)
<details><summary>show details</summary>
<p>

      This filter allows the user to make the image darker or lighter by 50%

</p>
 
</details>

> ### Filter 7: Detect Image Edges
![image](https://user-images.githubusercontent.com/101745968/161275768-74c228dd-5571-422b-81b3-e224a3377164.png)
<details><summary>show details</summary>
<p>

      This function finds the edges of the drawings in the image and turns the image into a skeleton version
      of the original as if it is drawn with pencil without coloring as shown. 

</p>
 
</details>

> ### Filter 8: Enlarge Image
![image](https://user-images.githubusercontent.com/101745968/161275978-43e3c1d9-b597-44fe-9544-59fb3c5eaf12.png)
<details><summary>show details</summary>
<p>

      This filter allows the user to enlarge one of the four quarters of the image into a separate new image.

</p>
 
</details>

> ### Filter 9: Shrink Image
![image](https://user-images.githubusercontent.com/101745968/161276203-268df67e-5f51-44d8-95c3-cc0244584c60.png)
<details><summary>show details</summary>
<p>

      This filter allows the user to shrink the image dimensions to 1/2, 1/3 or 1/4 the original dimensions.

</p>
 
</details>

> ### Filter a: Mirror Image
![image](https://user-images.githubusercontent.com/101745968/161276367-8944adbd-5314-4afa-92cc-10b6260442bc.png)
<details><summary>show details</summary>
<p>

      This filter mirrors 1/2 of the image as seen here in order: Left 1/2, Right 1/2, Upper 1/2 and Lower 1/2.

</p>
 
</details>

> ### Filter b: Shuffle Image
![image](https://user-images.githubusercontent.com/101745968/161276619-dcdc7f89-4d90-4e65-ac31-ba96525c0c44.png)
<details><summary>show details</summary>
<p>

      Assume the image consist of 4 quarters as shown
      the user enters the order he wants to the quarters in the new image. Wrong input is rejected.

</p>
 
```
  Assume he entered 4 3 2 1 he gets image 1. Or if he enters 3 1 4 2 he gets image 2. User can enter any order he likes.
```
 
</details>

> ### Filter c: Blur Image
![image](https://user-images.githubusercontent.com/101745968/161276803-0600dc0d-4209-448a-b3fd-96467c0ba167.png)
<details><summary>show details</summary>
<p>

      This filter produces a bury version of the image.

</p>
 
</details>
