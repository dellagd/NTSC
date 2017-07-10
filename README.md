# NTSC
Collection of work/projects I've done involving NTSC. 

Check out the diagram below that outlines the components of an NTSC signal for broadcasting images in YUV color with audio. To simplify as much as possible, NTSC allows for the transmission of a YUV image at either 29.97 or 59.94 frames per second. This is done by projecting either ~486 or ~242 horizontal lines of image onto the display, respectively. There is no hard resolution such as this on each line. Instead, the analog signal that occupies the indicated 52.6 microseconds below compose the data on each line. For the purposes of handling this digitally, I broke that space into 526 samples, creating 526 'pixels'. With this decision, my digital NTSC implementation therefore runs at 10 million samples per second, which seems to approximate the true analog signal well enough for hobby purposes.

All together, if running with the ~60 FPS non-interlaced standard, this means that a 526x242 image will be converted to NTSC and output. When viewed in the traditional sense, this would severely distort the image, but really the only controlling factor to the displayed image shape will be the NTSC display (such as a television). If you intend to recieve the signal on a square display, start out with a square image. The resize to 526x242 is only for the purpose of packaging the signal into the NTSC signal.

![alt text](NTSC_Signal_Diagram.png)
