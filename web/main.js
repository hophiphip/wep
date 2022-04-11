import Alpine from 'alpinejs';

import renderPlain from '../src/plain/index.js';
import renderTriangle from '../src/triangle/index.js';
import { render as renderUniforms, pause as pauseUniforms, unpause as unpauseUniforms } from '../src/uniforms/index.js';

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
            
            isPaused: false,

            /**
             * Called on element initialization.
             * @param {HTMLElement} element 
             */
            onInitialized: function (element) {
                this.renderer(element, this.onContextLost);

                // Pause rendering when canvas is out of view
                if(!!window.IntersectionObserver) { 
                    const observer = new IntersectionObserver(function (element, observer) {
                        if (element.intersectionRatio != 1 && !this.isPaused) {
                            pauseUniforms();
                            this.isPaused = true;
                        }
                        else if (this.isPaused) {
                            unpauseUniforms();
                            this.isPaused = false;
                        }
                    }, { threshold: 0.7 }); // unpause when 70% is seen

                    observer.observe(element);
                }
            },
        }, 
    ],
}));

Alpine.start();