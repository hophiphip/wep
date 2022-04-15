import shadersWasm from './dist/shaders.wasm'; // import .wasm file for bundler to detect it
import shaders from './dist/shaders.js';

let pauseShaders   = () => {};
let unpauseShaders = () => {};

/**
 * Start rendering.
 * @param {HTMLElement} canvas 
 * @param {EventListenerOrEventListenerObject} onWebGlContextLost
 */
export function render(canvas, onWebGlContextLost) {
    shaders().then(Shaders => {
        
        Shaders.canvas = (function () {
            canvas.addEventListener('webglcontextlost', function (evt) {
                onWebGlContextLost();
                evt.preventDefault();
            }, false);

            return canvas;
        })();

        pauseShaders   = Shaders._set_pause;
        unpauseShaders = Shaders._unset_pause;

        window.Shaders = Shaders;

        Shaders.callMain();
    });
}

export function pause() {
    pauseShaders();
}

export function unpause() {
    unpauseShaders();
}