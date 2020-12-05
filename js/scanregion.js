class ScanRegion {
  constructor() {
    this.size = 50;

    this.left = width / 2 - this.size / 2;
    this.top = height / 2 - this.size / 2;
    this.right = this.left + this.size;
    this.bottom = this.top + this.size;
    this.totalScanPixels = this.size * this.size;
  }

  draw() {
    stroke(0, 255, 0);
    noFill();
    rect(this.left, this.top, this.size, this.size);
  }

  getMeanRGB(scanRegion) {
    loadPixels();

    var meanR = 0,
      meanG = 0,
      meanB = 0;

    for (var y = this.top; y < this.bottom; y++) {
      for (var x = this.left; x < this.right; x++) {
        meanR += pixels[4 * (y * width + x)];
        meanG += pixels[4 * (y * width + x) + 1];
        meanB += pixels[4 * (y * width + x) + 2];
      }
    }

    meanR /= this.totalScanPixels;
    meanG /= this.totalScanPixels;
    meanB /= this.totalScanPixels;

    updatePixels();

    return [meanR, meanG, meanB];
  }

}