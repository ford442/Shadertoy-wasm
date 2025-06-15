precision mediump int;
uniform int iFrameRate;
uniform int iFrame;uniform float iTime;uniform float iTimeDelta;uniform vec4 iDate;
uniform float iChannelTime[4];uniform vec3 iChannelResolution[4];uniform vec3 iResolution;
uniform vec4 iMouse;uniform sampler2D iChannel0;uniform sampler2D iChannel1;uniform sampler2D iChannel2;
uniform sampler2D iChannel3;
out vec4 fragColor;
