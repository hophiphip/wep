import render from '../src/plain/index.js';

const canvas = document.getElementById('canvas');

const onWebGlContextLost = function () {
    alert('WebGL context lost. You will need to reload the page.'); 
}

render(canvas, onWebGlContextLost);