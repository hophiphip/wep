import triangleWasm from './dist/triangle.wasm'; // import .wasm file for bundler to detect it
import triangle from './dist/triangle.js';

/**
 * Start rendering.
 * @param {HTMLElement} canvas 
 * @param {EventListenerOrEventListenerObject} onWebGlContextLost
 */
export default function render(canvas, onWebGlContextLost) {
    triangle().then(Triangle => {
        
        Triangle.canvas = (function () {
            canvas.addEventListener('webglcontextlost', function (evt) {
                onWebGlContextLost();
                evt.preventDefault();
            }, false);

            return canvas;
        })();

        window.Triangle = Triangle;

        Triangle.callMain();
    });
}