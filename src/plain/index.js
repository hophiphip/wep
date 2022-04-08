import plainWasm from './plain.wasm'; // import .wasm file for bundler to detect it
import plain from './plain.js';

/**
 * Start rendering.
 * @param {HTMLElement} canvas 
 * @param {EventListenerOrEventListenerObject} onWebGlContextLost
 */
export default function render(canvas, onWebGlContextLost) {
    plain().then(Plain => {
        
        Plain.canvas = (function () {
            canvas.addEventListener('webglcontextlost', function (evt) {
                onWebGlContextLost();
                evt.preventDefault();
            }, false);

            return canvas;
        })();

        window.Plain = Plain;

        Plain.callMain();
    });
}