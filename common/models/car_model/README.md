## 关于dae模型文件的使用

### 1. 将modols作为package而存在
> 目的是为了能够在程序中直接使用`"package://car_model/ferrari/dae.DAE`使用

### 2. 修改dae模型中的贴图文件的路径
> Linux下,贴图路径改成相对路径;
比如:
` <image id="Map #14-image" name="Map #14"><init_from>./door_window_diffuse.jpg</init_from></image>`
