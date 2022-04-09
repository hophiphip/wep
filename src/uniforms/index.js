import uniformsWasm from './dist/uniforms.wasm'; // import .wasm file for bundler to detect it
import uniforms from './dist/uniforms.js';

/**
 * Start rendering.
 * @param {HTMLElement} canvas 
 * @param {EventListenerOrEventListenerObject} onWebGlContextLost
 */
export default function render(canvas, onWebGlContextLost) {
    uniforms().then(Uniforms => {
        
        Uniforms.canvas = (function () {
            canvas.addEventListener('webglcontextlost', function (evt) {
                onWebGlContextLost();
                evt.preventDefault();
            }, false);

            return canvas;
        })();

        window.Uniforms = Uniforms;

        Uniforms.callMain();
    });
}