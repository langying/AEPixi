var renderer = PIXI.autoDetectRenderer(640, 1136);
document.body.appendChild(renderer.view);

// create the root of the scene graph
var stage = new PIXI.Container();

PIXI.loader
    .add('mc.json')
    .load(onAssetsLoaded);

function onAssetsLoaded()
{
    // create an array to store the textures
    var explosionTextures = [],
        i;

    for (i = 0; i < 26; i++)
    {
         var texture = PIXI.Texture.fromFrame('Explosion_Sequence_A ' + (i+1) + '.png');
         explosionTextures.push(texture);
    }

    for (i = 0; i < 50; i++)
    {
        // create an explosion MovieClip
        var explosion = new PIXI.MovieClip(explosionTextures);

        explosion.x = Math.random() * 640;
        explosion.y = Math.random() * 1136;
        explosion.anchorX = 0.5;
        explosion.anchorY = 0.5;

        explosion.rotation = Math.random() * Math.PI;
        explosion.scale = new PIXI.Point(0.75 + Math.random() * 0.5);

        explosion.gotoAndPlay(Math.random() * 27);

        stage.addChild(explosion);
    }

    // start animating
    requestAnimationFrame(animate);
}

function animate() {
    renderer.render(stage);

    requestAnimationFrame(animate);
}
