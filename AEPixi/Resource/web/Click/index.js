var renderer = PIXI.autoDetectRenderer(640, 1136,{backgroundColor : 0x1099bb});
document.body.appendChild(renderer.view);

// create the root of the scene graph
var stage = new PIXI.Container();

var sprite = PIXI.Sprite.fromImage('bunny.png');

sprite.x = 230.0;
sprite.y = 264.0;
sprite.interactive = true;
sprite.on('mousedown', onDown);
sprite.on('touchstart', onDown);

stage.addChild(sprite);

function onDown (eventData) {
    
    sprite.scaleX += 0.3;
    sprite.scaleY += 0.3;
}
// start animating
animate();

function animate() {
    
    requestAnimationFrame(animate);
    
    // render the root container
    renderer.render(stage);
}
