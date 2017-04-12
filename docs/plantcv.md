# PlantCV


[PlantCV](http://plantcv.danforthcenter.org) is a python library based on OpenCV that allows to compute plants caracteristics based on computer vision.http://
It was used to compute the LAI - Leaf Area Index of the plants.

The developed python script is hgco/scrpits/compute_LAI.py and is called by the linux script hgco/scripts/compute_LAI.sh that uses raspstill to take a foto and that PlantCV will process it.


## Documentation
* [Read the docs](http://plantcv.readthedocs.io/en/latest/)

The [Multi plant pipeline](http://plantcv.readthedocs.io/en/latest/multi-plant_tutorial/) was used to split the different plants.
Afterwards the [VIS pipeline](http://plantcv.readthedocs.io/en/latest/vis_tutorial/) was called for each of the splited images.

## Installing

There was some problems installing PlantCV in raspberry pi, but they were 
overtaken as decribed in this [issue](https://github.com/danforthcenter/plantcv/issues/136) and this [issue](https://github.com/danforthcenter/plantcv/issues/134)


