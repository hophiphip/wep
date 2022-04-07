import triangle from './triangle.js';

const Triangle = await triangle();

/**
 * Start rendering.
 * @param {HTMLElement} canvas 
 * @param {EventListenerOrEventListenerObject} onWebGlContextLost
 */
export default function render(canvas, onWebGlContextLost) {
    Triangle.canvas = (function () {
        canvas.addEventListener('webglcontextlost', function (evt) {
            onWebGlContextLost();
            evt.preventDefault();
        }, false);

        return canvas;
    })();

    window.Triangle = Triangle;

    Triangle.callMain();
}