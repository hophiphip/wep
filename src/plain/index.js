import plainWasm from './dist/plain.wasm'; // import .wasm file for bundler to detect it
import plain from './dist/plain.js';

let setPausePlain = () => {};

/**
 * Start rendering.
 * @param {HTMLElement} canvas 
 * @param {EventListenerOrEventListenerObject} onWebGlContextLost
 */
export function render(canvas, onWebGlContextLost) {
    plain().then(Plain => {
        
        Plain.canvas = (function () {
            canvas.addEventListener('webglcontextlost', function (evt) {
                onWebGlContextLost();
                evt.preventDefault();
            }, false);

            return canvas;
        })();

        window.Plain = Plain;

        setPausePlain = Plain._setPause;

        Plain.callMain();
    });
}

/**
 * Set render pause state.
 * @param {Boolean} isPaused 
 */
export function setPause(isPaused) {
    setPausePlain(isPaused);
}