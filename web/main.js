import renderPlain from '../src/plain/index.js';
import renderTriangle from '../src/triangle/index.js';

const plainColorCanvas = document.getElementById('plain-color');
const triangleCanvas = document.getElementById('triangle');

const onWebGlContextPlainColorLost = function () {
    alert('WebGL plain color context lost. You will need to reload the page.'); 
}

const onWebGlContextTriangleLost = function () {
    alert('WebGL triangle color context lost. You will need to reload the page');
}

renderPlain(plainColorCanvas, onWebGlContextPlainColorLost);
renderTriangle(triangleCanvas, onWebGlContextTriangleLost);