#! /usr/bin/python

import prman

ri = prman.Ri()
rendertarget = "helloworld.rib"
ri.Begin(rendertarget)  # set rendertarget to ri.RENDER to render pixels)
ri.Display("helloworld.exr", "openexr", "rgba")
ri.Format(512,512,1)
ri.Projection(ri.PERSPECTIVE, {ri.FOV: 45}) # standard Ri tokens are available
ri.Translate(0,0,10)
ri.WorldBegin()
ri.Geometry("teapot")
ri.WorldEnd()
ri.End()
