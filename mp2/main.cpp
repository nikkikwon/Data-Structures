#include"Image.h"
#include"StickerSheet.h"

int main() {
  Image alma;
  alma.readFromFile("tests/alma.png");
  
  Image i;
  i.readFromFile("tests/i.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);

  StickerSheet paper(alma, 5);
  sheet.addSticker(i, 50, 100);

  StickerSheet plane(alma, 5);
  sheet.addSticker(i, 90, 10);

  Image myImage;
  myImage = sheet.render();
  myImage.writeToFile("myImage.png");

  return 0;
}




