Stereoscopic Depth Detection Using Two Cameras
==============================================

The purpose of this project is to use two horizontally aligned cameras 
to detect the depth of images in the field of view.  It does this by 
comparing the blocks in one camera to blocks in the other looking for 
the closest match. Knowing the position of one block in both images the 
distance away from the cameras can then be detected. 


How to use
----------

1. Clone this repository
2. Create a `ip_repo` folder
3. Clone all of the dependencies into `ip_repo`
4. Add the `ip_repo` folder as an IP location in the main project
5. Open project in vivado
6. Generate bitstream
7. Program a Nexys 4 DDR board
8. Run the software from the SDK

Structure
---------

* stereoscopic_depth.xpr: The vivado project
* stereoscopic_depth.srcs: The folder containing the sources
* stereoscopic_depth.sdk: Contains the software to run the system
* docs: Contains a copy of the design report

Dependencies
------------

The following additional IPs are required

* [ov7670_axi_stream_capture](https://github.com/marknsikora/ov7670_axi_stream_capture)
* [ov7670_i2c_controller](https://github.com/marknsikora/ov7670_i2c_controller)
* [stereoscopic_comperator_ip](https://github.com/marknsikora/stereoscopic_comperator_ip)
* [vga_ip](https://github.com/marknsikora/vga_ip)

Authors
-------

* Robert An
* Kai Chun Chou
* Mark Sikora

License
-------

GNU AGPLv3
