#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *image, *outputImage, *lecturas, *fptr1, *fptr2, *fptr3, *fptr4;;
    image = fopen("greenland.bmp","rb");          //Imagen original a transformar
    outputImage = fopen("img2_dd.bmp","wb");    //Imagen transformada
    fptr1=fopen("Red.txt","w");
    fptr2=fopen("Green.txt","w");
    fptr3=fopen("Blue.txt","w");
    fptr4=fopen("Gray.txt","w");
    long ancho;
    long alto;
    unsigned char r, g, b;               //Pixel
    unsigned char* ptr;

    int totalR[255] = {};
    int totalG[255]= {};
    int totalB[255] = {};
    int totalGray[255] = {};

    unsigned char xx[54];
    int cuenta = 0;
    for(int i=0; i<54; i++) {
      xx[i] = fgetc(image);
      fputc(xx[i], outputImage);   //Copia cabecera a nueva imagen
    }
    ancho = (long)xx[20]*65536+(long)xx[19]*256+(long)xx[18];
    alto = (long)xx[24]*65536+(long)xx[23]*256+(long)xx[22];
    printf("largo img %li\n",alto);
    printf("ancho img %li\n",ancho);

    ptr = (unsigned char*)malloc(alto*ancho*3* sizeof(unsigned char));

    while(!feof(image)){
      b = fgetc(image);
      g = fgetc(image);
      r = fgetc(image);

      totalB[(int)b]+=1;
      totalG[(int)g]+=1;
      totalR[(int)r]+=1;

      unsigned char pixel = 0.21*r+0.72*g+0.07*b;

      totalGray[(int)pixel]+=1;

      ptr[cuenta] = pixel; //b
      ptr[cuenta+1] = pixel; //g
      ptr[cuenta+2] = pixel; //r


      cuenta++;

    }                                        //Grises
    cuenta = ancho;
    for (int i = 0; i < alto*ancho*3; ++i) {
      fputc(ptr[i+(cuenta*3)+2], outputImage);
      fputc(ptr[i+(cuenta*3)+1], outputImage);
      fputc(ptr[i+(cuenta*3)], outputImage);
      cuenta--;
      if (cuenta == 0){
        cuenta = ancho;
      }
    }

    for (int i = 0; i<256; i++) {
        fprintf(fptr1, "%i\t %i\n",i,totalR[i]);
    }
    fclose(fptr1);

    for (int i = 0; i<256; i++) {
        fprintf(fptr2, "%i\t %i\n",i,totalG[i]);
    }
    fclose(fptr2);

    for (int i = 0; i<256; i++) {
        fprintf(fptr3, "%i\t %i\n",i,totalB[i]);
    }
    fclose(fptr3);

    for (int i = 0; i<256; i++) {
        fprintf(fptr4, "%i\t %i\n",i,totalG[i]);
    }
    fclose(fptr4);

    free(ptr);
    fclose(image);
    fclose(outputImage);
    return 0;
}
