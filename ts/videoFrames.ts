const videoElement = document.getElementById("mvi") as HTMLVideoElement;
let canvas: OffscreenCanvas | null = null;
let context: OffscreenCanvasRenderingContext2D | null = null;

const processFrameCallback = (now: any, metadata: any) => {
    // Using an async IIFE to handle createImageBitmap promise
    (async () => {
        if (videoElement.readyState < videoElement.HAVE_CURRENT_DATA) {
            // @ts-ignore
            videoElement.requestVideoFrameCallback(processFrameCallback);
            return;
        }

        try {
            const imageBitmap = await createImageBitmap(videoElement);

            if (!canvas) {
                canvas = new OffscreenCanvas(imageBitmap.width, imageBitmap.height);
                context = canvas.getContext("2d") as OffscreenCanvasRenderingContext2D;
            }

            if (context) {
                context.drawImage(imageBitmap, 0, 0);
                const imageData = context.getImageData(0, 0, canvas.width, canvas.height);
                const frameData = imageData.data.buffer; // Raw pixel data (Uint8ClampedArray)
                // FS.writeFile("/video/frame.gl", new Uint8Array(frameData));
            }
            imageBitmap.close();
        } catch (e) {
            console.error("Failed to process video frame:", e);
        }

        // Request the next frame to continue the loop
        // @ts-ignore
        if (videoElement.requestVideoFrameCallback) {
            videoElement.requestVideoFrameCallback(processFrameCallback);
        }
    })();
};

videoElement.addEventListener("play", () => {
  // @ts-ignore
  if (videoElement.requestVideoFrameCallback) {
    videoElement.requestVideoFrameCallback(processFrameCallback);
  } else {
    // Fallback for browsers that don't support requestVideoFrameCallback
    const processFrame = () => {
        if (videoElement.readyState >= videoElement.HAVE_CURRENT_DATA) {
            (async () => {
                try {
                    const imageBitmap = await createImageBitmap(videoElement);
                    if (!canvas) {
                        canvas = new OffscreenCanvas(imageBitmap.width, imageBitmap.height);
                        context = canvas.getContext("2d") as OffscreenCanvasRenderingContext2D;
                    }
                    if (context) {
                        context.drawImage(imageBitmap, 0, 0);
                        const imageData = context.getImageData(0, 0, canvas.width, canvas.height);
                        const frameData = imageData.data.buffer;
                        // FS.writeFile("/video/frame.gl", new Uint8Array(frameData));
                    }
                    imageBitmap.close();
                } catch (e) {
                    console.error("Failed to process video frame:", e);
                }
            })();
        }
        requestAnimationFrame(processFrame);
    };
    requestAnimationFrame(processFrame);
  }
});
