import plain from './plain.js';

const Plain = await plain();

/**
 * Start rendering.
 * @param {HTMLElement} canvas 
 * @param {EventListenerOrEventListenerObject} onWebGlContextLost
 */
export default function render(canvas, onWebGlContextLost) {
    Plain.canvas = (function () {
        canvas.addEventListener('webglcontextlost', function (evt) {
            onWebGlContextLost();
            evt.preventDefault();
        }, false);

        return canvas;
    })();

    window.Plain = Plain;

    Plain.callMain();
}