var renderer = PIXI.autoDetectRenderer(640, 1136);
document.body.appendChild(renderer.view);

// create the root of the scene graph
var stage = new PIXI.Container();

PIXI.loader.add('fighter.json').load(onAssetsLoaded);

var movie;

function onAssetsLoaded()
{
    // create an array of textures from an image path
    var frames = [];
    
    for (var i = 0; i < 30; i++) {
        var val = i < 10 ? '0' + i : i;
        
        // magically works since the spritesheet was loaded with the pixi loader
        frames.push(PIXI.Texture.fromFrame('rollSequence00' + val + '.png'));
    }
    
    
    // create a MovieClip (brings back memories from the days of Flash, right ?)
    movie = new PIXI.MovieClip(frames);
    
    /*
     * A MovieClip inherits all the properties of a PIXI sprite
     * so you can change its position, its anchor, mask it, etc
     */
    movie.position = new PIXI.Point(300, 300);
    
    movie.anchor = new PIXI.Point(0.5, 0.5);
    movie.animationSpeed = 0.5;
    
    movie.play();
    
    stage.addChild(movie);
    
    animate();
}

function animate() {
    movie.rotation += 0.01;
    
    // render the stage container
    renderer.render(stage);
    
    requestAnimationFrame(animate);
}
