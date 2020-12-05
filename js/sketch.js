var video;
var scanRegion;
var videoSources;

// This method can be removed after the source ID has been determined.
function gotSources(sources) {
  videoSources = sources;
  for (var i = 0; i !== sources.length; ++i) {
    if (sources[i].kind === 'audioinput') {
      console.log('audio: '+sources[i].label+' ID: '+sources[i].id);
    } else if (sources[i].kind === 'videoinput') {
      console.log('video: '+sources[i].label+' ID: '+sources[i].id);
      console.log(sources[i]);
    } else {
      console.log('Some other kind of source: ', sources[i].kind);
    }
  }
}

function setup() {
  
  pixelDensity(1);
  createCanvas(400, 400);

  var constraints = {
    audio: false,
    video: {
      deviceId: "faa7b1fb3a44558de3cdaba8a3df3f9c1650438aaa43b11a10d73b97f83dc6bd"      
    }
  };
    
  navigator.mediaDevices.enumerateDevices().then(gotSources);
  
  //const capabilities = track.getCapabilities()

  video = createCapture(constraints);
  video.hide();
  console.log(video);

  scanRegion = new ScanRegion();
  console.log(scanRegion);
  background(0);
}



function draw() {
  if (frameCount%width == 0)
    background(0);
  
  
  image(video, 0, 0, width, height-100);
  var meanRGB = scanRegion.getMeanRGB(scanRegion);
 
  scanRegion.draw();
  fill(255,0,0);
  noStroke();
  ellipse(frameCount%width, height-meanRGB[0]/5, 5,5);  
  fill(0,255,0);
  ellipse(frameCount%width, height-meanRGB[1]/5, 5,5);  
  fill(0,0,255);
  ellipse(frameCount%width, height-meanRGB[2]/5, 5,5);  
}
