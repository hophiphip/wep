import Alpine from 'alpinejs';

import renderPlain from '../src/plain/index.js';
import renderTriangle from '../src/triangle/index.js';
import renderUniforms from '../src/uniforms/index.js';

window.Alpine = Alpine; 

const onWebGlContextPlainColorLost = function () { alert('WebGL plain color context lost. You will need to reload the page.');   }
const onWebGlContextTriangleLost   = function () { alert('WebGL triangle color context lost. You will need to reload the page'); }
const onWebGlContextUniformsLost   = function () { alert('WebGL uniforms context lost. You will need to reload the page');       }

Alpine.data('main', () => ({
    renderers: [
        { 
            id: 'plain', 
            title: 'Hello Window',
            reference: 'https://learnopengl.com/Getting-started/Hello-Window',
            renderer: renderPlain, 
            onContextLost: onWebGlContextPlainColorLost,
            
            /**
             * Called on element initialization.
             * @param {HTMLElement} element 
             */
            onInitialized: function (element) {
                this.renderer(element, this.onContextLost);
            },
        }, 
        { 
            id: 'triangle', 
            title: 'Hello Triangle',
            reference: 'https://learnopengl.com/Getting-started/Hello-Triangle',
            renderer: renderTriangle,
            onContextLost: onWebGlContextTriangleLost,  

            /**
             * Called on element initialization.
             * @param {HTMLElement} element 
             */
            onInitialized: function (element) {
                this.renderer(element, this.onContextLost);
            },
        }, 
        { 
            id: 'uniforms', 
            title: 'Uniforms',
            reference: 'https://learnopengl.com/Getting-started/Shaders', 
            renderer: renderUniforms, 
            onContextLost: onWebGlContextUniformsLost,
            
            /**
             * Called on element initialization.
             * @param {HTMLElement} element 
             */
            onInitialized: function (element) {
                this.renderer(element, this.onContextLost);
            },
        }, 
    ],
}));

Alpine.start();