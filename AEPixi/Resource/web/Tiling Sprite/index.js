var renderer = PIXI.autoDetectRenderer(640, 1136);
document.body.appendChild(renderer.view);

// create the root of the scene graph
var stage = new PIXI.Container();

// create a texture from an image path
var texture = PIXI.Texture.fromImage('p2.png');

/* create a tiling sprite ...
 * requires a texture, a width and a height
 * in WebGL the image size should preferably be a power of two
 */
var tilingSprite = new PIXI.TilingSprite(texture, renderer.width, renderer.height);
stage.addChild(tilingSprite);

var count = 0;

animate();

function animate() {
    
    count += 0.005;
    
    tilingSprite.tileScaleX = 2 + Math.sin(count);
    tilingSprite.tileScaleY = 2 + Math.cos(count);
    
    tilingSprite.tilePositionX += 1;
    tilingSprite.tilePositionX += 1;
    
    // render the root container
    renderer.render(stage);
    
    requestAnimationFrame(animate);
}
