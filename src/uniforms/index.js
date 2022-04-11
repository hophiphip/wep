import uniformsWasm from './dist/uniforms.wasm'; // import .wasm file for bundler to detect it
import uniforms from './dist/uniforms.js';

let pauseUniforms   = () => {};
let unpauseUniforms = () => {};

/**
 * Start rendering.
 * @param {HTMLElement} canvas 
 * @param {EventListenerOrEventListenerObject} onWebGlContextLost
 */
export function render(canvas, onWebGlContextLost) {
    uniforms().then(Uniforms => {
        
        Uniforms.canvas = (function () {
            canvas.addEventListener('webglcontextlost', function (evt) {
                onWebGlContextLost();
                evt.preventDefault();
            }, false);

            return canvas;
        })();

        pauseUniforms   = Uniforms._set_pause;
        unpauseUniforms = Uniforms._unset_pause;

        window.Uniforms = Uniforms;

        Uniforms.callMain();
    });
}

export function pause() {
    pauseUniforms();
}

export function unpause() {
    unpauseUniforms();
}