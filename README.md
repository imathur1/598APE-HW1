# 598APE-HW1

## Quick Start
- Build and run the docker container:
    ```bash
    docker build -t cs598ape -f docker/Dockerfile .
    docker run -p 8000:8000 --privileged -it -v `pwd`:/host cs598ape /bin/bash
    ```
- Compile the program:
    ```bash
    make -j PROFILE=0
    ```
- Run the program on the test cases:
    ```bash
    ./test.sh pianoroom 500 500
    ./test.sh globe 1000 1000 24
    ./test.sh elephant 200 200
    ./test.sh realelephant 100 100
    ```

The tests evaluate the performance of rendering the scenes, while also comparing to a baseline without any optimizations to ensure correctness. For example, for pianoroom there is a baseline file `output/pianoroom_correct.ppm`

## Optimizations
A full analysis can be found in our paper, `Mini_Paper_1__Raytracer.pdf`
<div style="display: flex; flex-wrap: wrap; justify-content: space-between;">

  <div style="flex: 1; min-width: 300px; margin-right: 20px;">
    <h3>Globe Optimizations</h3>
    <table border="1" cellspacing="0" cellpadding="4">
      <thead>
        <tr>
          <th>Optimization</th>
          <th>Avg. Runtime (sec)</th>
          <th>Relative Speedup</th>
          <th>Hash</th>
        </tr>
      </thead>
      <tbody>
        <tr>
          <td>Baseline</td>
          <td>149.401</td>
          <td>--</td>
          <td>d649112</td>
        </tr>
        <tr>
          <td>Clang &amp; -O3</td>
          <td>87.353</td>
          <td>1.710</td>
          <td>2e154bc</td>
        </tr>
        <tr>
          <td>Pass-by-reference + const</td>
          <td>79.510</td>
          <td>1.098</td>
          <td>26828ab</td>
        </tr>
        <tr>
          <td>calcColor sort into find min</td>
          <td>62.792</td>
          <td>1.266</td>
          <td>54b0047</td>
        </tr>
        <tr>
          <td>Cache solveScaler</td>
          <td>61.583</td>
          <td>1.018</td>
          <td>d30fa51</td>
        </tr>
        <tr>
          <td>Inline vector fns</td>
          <td>59.333</td>
          <td>1.038</td>
          <td>a497a1f</td>
        </tr>
        <tr>
          <td>std::vector to store Shapes</td>
          <td>59.586</td>
          <td>0.996</td>
          <td>adcef25</td>
        </tr>
        <tr>
          <td>OpenMP</td>
          <td>20.617</td>
          <td>2.895</td>
          <td>12eb706</td>
        </tr>
        <tr>
          <td>cache animation file data</td>
          <td>18.044</td>
          <td>1.143</td>
          <td>ddf5d3b</td>
        </tr>
        <tr>
          <td>Swap Vector for glm::dvec3</td>
          <td>15.979</td>
          <td>1.129</td>
          <td>890fac4</td>
        </tr>
        <tr>
          <td>Use -O2 &amp; -march=native</td>
          <td>15.991</td>
          <td>1.000</td>
          <td>2d1de14</td>
        </tr>
      </tbody>
    </table>
  </div>

  <div style="flex: 1; min-width: 300px; margin-left: 20px;">
    <h3>Pianoroom Optimizations</h3>
    <table border="1" cellspacing="0" cellpadding="4">
      <thead>
        <tr>
          <th>Optimization</th>
          <th>Avg. Runtime (sec)</th>
          <th>Relative Speedup</th>
          <th>Hash</th>
        </tr>
      </thead>
      <tbody>
        <tr>
          <td>Baseline</td>
          <td>2.273</td>
          <td>--</td>
          <td>d649112</td>
        </tr>
        <tr>
          <td>Clang &amp; -O3</td>
          <td>1.104</td>
          <td>2.061</td>
          <td>2e154bc</td>
        </tr>
        <tr>
          <td>Pass-by-reference + const</td>
          <td>0.908</td>
          <td>1.214</td>
          <td>26828ab</td>
        </tr>
        <tr>
          <td>calcColor sort into find min</td>
          <td>0.678</td>
          <td>1.341</td>
          <td>54b0047</td>
        </tr>
        <tr>
          <td>Cache solveScaler</td>
          <td>0.555</td>
          <td>1.220</td>
          <td>d30fa51</td>
        </tr>
        <tr>
          <td>Inline vector fns</td>
          <td>0.603</td>
          <td>0.920</td>
          <td>a497a1f</td>
        </tr>
        <tr>
          <td>std::vector to store Shapes</td>
          <td>0.600</td>
          <td>1.005</td>
          <td>adcef25</td>
        </tr>
        <tr>
          <td>OpenMP</td>
          <td>0.218</td>
          <td>2.756</td>
          <td>12eb706</td>
        </tr>
        <tr>
          <td>getLightIntersection early exit</td>
          <td>0.211</td>
          <td>1.032</td>
          <td>0c1b1bd</td>
        </tr>
        <tr>
          <td>cache animation file data</td>
          <td>0.172</td>
          <td>1.224</td>
          <td>ddf5d3b</td>
        </tr>
        <tr>
          <td>Swap Vector for glm::dvec3</td>
          <td>0.133</td>
          <td>1.298</td>
          <td>890fac4</td>
        </tr>
        <tr>
          <td>Use -O2 &amp; -march=native</td>
          <td>0.130</td>
          <td>1.021</td>
          <td>2d1de14</td>
        </tr>
      </tbody>
    </table>
  </div>

</div>


This repository contains code for homework 1 of 598APE.

In particular, this repository is an implementation of a Raytracer.

To compile the program run:
```bash
make -j
```

To clean existing build artifacts run:
```bash
make clean
```

This program assumes the following are installed on your machine:
* A working C++ compiler (g++ is assumed in the Makefile)
* make
* ImageMagick (for importing and exporting non-ppm images)
* FFMpeg (for exporting movies from image sequences)

The raytracer program here is general and can be used to generate any number of different potential scenes.

Once compiled, one can call the raytracer program as follows:
```bash
./main.exe --help
# Prints the following
# Usage ./main.exe [-H <height>] [-W <width>] [-F <framecount>] [--movie] [--no-movie] [--png] [--ppm] [--help] [-o <outfile>] [-i <infile>] [-a <animationfile>]
```

The raytracer program takes a scene file (a text file ending in .ray) and generates an image or sequence of images corresponding to the specified scene.

One can tune the height, width, and format of the image being generated with optional command line arguments. For example, let's generate an 500x500 image corresponding to the scene in `inputs/pianoroom.ray`, in PPM format.

```bash
./main.exe -i inputs/pianoroom.ray --ppm -o output/pianoroom.ppm -H 500 -W 500
```

As we run the program, we see the following output:
```
Done Frame       0|
Total time to create images=1.334815 seconds
```

We have placed timer code surrounding the main computational loop inside main.cpp. It is your goal to reduce this runtime as much as possible, while maintaining or increasing the complexity (i.e. resolution, number of frames) of the scene.

Here we see that the image took 1.3 seconds to run and produced a result in `output/pianoroom.ppm`. Input and output of images is already handled by the library. In particular, the PPM format (see https://en.wikipedia.org/wiki/Netpbm for an example), represents images as text for data -- which makes it easy to input and output without the use of a library. However, as this is not the most efficient, this application uses the tool ImageMagick tool to convert to and from the PPM formats. Convert the PPM to a PNG with the following command:
```bash
convert output/pianoroom.ppm output/pianoroom.png
```

## Input Programs
This project contains three (arguably four) input programs for you to optimize.

### PianoRoom

A simple room with a reflecting checkerboard floor, a stairwell, a sphere, a circular rug, and a mirror ref.

Here we want to produce the highest resolution single image of this format, as fast as possible. The relevant command for producing an output is:

```bash
./main.exe -i inputs/pianoroom.ray --ppm -o output/pianoroom.ppm -H 500 -W 500
```

### Globe

A video of the Earth floating on top of a sea with a sky in the background. The Earth and clouds are rotating (in opposite directions), and the sea beneath reflects the scene above, and moves.

Here we want to produce the highest resolution video, as fast as possible. The relevant command for producing an output is:

```bash
./main.exe -i inputs/globe.ray --ppm  -a inputs/globe.animate --movie -F 24 
```

Here, as we are generating multiple frames, the extra command `-a <animationfile>` is used to pass in a sequence of commands to generate subsequent frames.

The number of frames we wish to generate (24) is passed in as `-F <numframes>`.

Here we will produce 24 individual images for each frame. To produce a playable movie out of these images, the `--movie` command will call a program called FFMpeg to produce a playable video.

### Elephant

A mesh of objects. In practical graphics applications, designing a primitive for each possible object is too complex. Instead, one builds up a mesh of triangles to represent the object being shown. Given sufficiently many triangles, we can represent arbitrarily complex structures. Here, we wish to make a video circling around a Mesh object which we import.

The simple version of this program is generated by the following command:
```bash
./main.exe -i inputs/elephant.ray --ppm  -a inputs/elephant.animate --movie -F 24 -W 100 -H 100 -o output/sphere.mp4 
```

Note the reduced resolution (as the initial unoptimized code can be somewhat slow).

This initial mesh represents a sphere with 3168 triangles.

Here we produce a video in which we have the camera circles around the object.

If we inspect the input file `inputs/elephant.ray` we see that it loads the mesh from two files, as defined by the line
```
data/x.txt 1586 data/f.txt 3168 -1.58 -.43 2.7
```

The goal here is to speed up the program sufficiently to make a high resolution circle of the elephant mesh (found in `data/elepx.txt` and `data/elepf.txt`), which contains 111748 triangles. One can edit the `.ray` file and comment out the sphere mesh and replace it with `data/elepx.txt 62779 data/elepf.txt 111748 -1.58 -.43 2.7` (this is done in `inputs/realelephant.ray`).

## Code Overview

The raytracer contains several core utilities, defined in different files.

### Camera

The Camera class contains information about the position and direction we are facing. An image is constructed by creating a grid of points and sending out rays from each of these points, and determining what objects they collide with. Each result becomes an individual pixel in our resulting image.

### Shape

Each object in our scene is defined as a shape. There are several shapes subclasses in the application. This includes a plane (an infinitely long flat surface), a sphere (a collection of points equidistant from a center), a disk (a flat surface whose points are within a given distance of a center), a box (a flat rectangle), and a triangle.

Shapes have a position in space, and potentially an orientation (i.e. direction they face, as defined with the angles yaw pitch and roll).

Shapes also have a texture defining what color of each point of the shape, and optionally a "normalMap" texture which defines how light bounces off each point.

Core methods within shape include:
* `getIntersection`, which defines whether a given light ray will hit the shape, and if so returns time it takes the light to hit it (otherwise infinity).
* `getLightIntersection`: Given that a ray hits the shape, determine how a light source will illuminate the shape at that point based off of the color of the object, and its spectral properties (i.e. opaque, reflective, aminent lighting).
* `getNormal` determine the normal axis to the point of collision, in order to compute the direction in which light will bounce off the object.

### Texture

A texture object defines what color will be applied at a point in space. There are two textures implemented: a single color for all points, and one loaded from an image. Textures are used to define both the color of an object, and also can optionally be used to define normal axes for an object (using data stored in rgb to define the xyz axis).

### Light

Light objects illuminate a scene, resulting in differences in gradients of colors on an object and shadows. Lights have a color and a position.

### Autonoma

An Autonoma is a base class used to hold all of the shapes in scope, the camera, and all lights.


## Docker

For ease of use and installation, we provide a docker image capable of running and building code here. The source docker file is in /docker (which is essentially a list of commands to build an OS state from scratch). It contains the dependent compilers, and some other nice things.

You can build this yourself manually by running `cd docker && docker build -t <myusername>/598ape`. Alternatively we have pushed a pre-built version to `wsmoses/598ape` on Dockerhub.

You can then use the Docker container to build and run your code. If you run `./dockerrun.sh` you will enter an interactive bash session with all the packages from docker installed (that script by default uses `wsmoses/598ape`, feel free to replace it with whatever location you like if you built from scratch). The current directory (aka this folder) is mounted within `/host`. Any files you create on your personal machine will be available there, and anything you make in the container in that folder will be available on your personal machine.

To use pprof (within Docker), first compile your code with the requisite library linked and profiling enabled around a section of the code you want to profile. Run the program and it will create a profile file (i.e. `my_profile.pprof`). You can now run an interactive webserver for profiling with `$HOME/go/bin/pprof -http "0.0.0.0:8000" ./my_profile.prof`. You can then open a web browser on your local machine by going to `http://localhost:8000/`.
