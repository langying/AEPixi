var renderer = new PIXI.Renderer(640, 1136);
document.body.appendChild(renderer.view);

// create the root of the scene graph
var stage = new PIXI.Container();

// create a texture from an image path
var texture = PIXI.Texture.fromImage('bunny.png');

// create a new Sprite using the texture
var bunny = new PIXI.Sprite(texture);

// center the sprite's anchor point
bunny.anchor = new PIXI.Point(0.5, 0.5);
bunny.scale  = new PIXI.Point(20, 10);
// move the sprite to the center of the screen
bunny.position = new PIXI.Point(200, 300);

stage.addChild(bunny);

// start animating
animate();
function animate() {
    requestAnimationFrame(animate);
    
    // just for fun, let's rotate mr rabbit a little
    bunny.rotation += 0.1;
    
    // render the container
    renderer.render(stage);
}