import renderPlain from '../src/plain/index.js';
import renderTriangle from '../src/triangle/index.js';
import renderUniforms from '../src/uniforms/index.js';

const plainColorCanvas = document.getElementById('plain');
const triangleCanvas = document.getElementById('triangle');
const uniformsCanvas = document.getElementById('uniforms');

const onWebGlContextPlainColorLost = function () {
    alert('WebGL plain color context lost. You will need to reload the page.'); 
}

const onWebGlContextTriangleLost = function () {
    alert('WebGL triangle color context lost. You will need to reload the page');
}

const onWebGlContextUniformsLost = function () {
    alert('WebGL uniforms context lost. You will need to reload the page');
}

renderPlain(plainColorCanvas, onWebGlContextPlainColorLost);
renderTriangle(triangleCanvas, onWebGlContextTriangleLost);
renderUniforms(uniformsCanvas, onWebGlContextUniformsLost);