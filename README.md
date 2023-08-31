# ChatGPT-SD-Integration-UE5
 UE5 plug-in integrating ChatGPT and SD.

# 使用方法
## Stable Diffusion
- 先启动SD WebUI，打开其API调用功能<br>
![15c069268d5edb40fb5a8816608f8a7abdb3129d3886ea56abe19dc94b646cf7.png](https://mytechplayer.com/upload/2023/08/15c069268d5edb40fb5a8816608f8a7abdb3129d3886ea56abe19dc94b646cf7-2d5a74af1f184a0bae282f6602838cf1.png)
- 示例蓝图BP_SDSample
构造参数，发起请求，回调设置Image
![ee985199b49d9d380e83853133a94ff76e6e9bee12170bce7beecc65b7bf5d9c.png](https://mytechplayer.com/upload/2023/08/ee985199b49d9d380e83853133a94ff76e6e9bee12170bce7beecc65b7bf5d9c-7dfd811dbf434dc2abf2ccbe080bb7b0.png)
- 生成结果
![7aa87ce9ef4274bb1b8aa40912e14ade54b45e56c2e5e3b7e110ed2bc84fd7b8.png](https://mytechplayer.com/upload/2023/08/7aa87ce9ef4274bb1b8aa40912e14ade54b45e56c2e5e3b7e110ed2bc84fd7b8-665b50653e614b64803873de96867b22.png)
## ChatGPT
- 在初始化中设置一个全局的Api-Key
![9ee0be54ed365cd6779432845094f8e83ca481d553d4eae2c8409eb027eb6b18.png](https://mytechplayer.com/upload/2023/08/9ee0be54ed365cd6779432845094f8e83ca481d553d4eae2c8409eb027eb6b18-aa1c51d2bfcc4322862e49ece9aaf01a.png)

- 蓝图BP_ChatGPTSample,调用异步任务节点即可
![da8f3aa5cfd613ea814953e51990c4a4843d13f317113931dd13a920273c9bd2.png](https://mytechplayer.com/upload/2023/08/da8f3aa5cfd613ea814953e51990c4a4843d13f317113931dd13a920273c9bd2-ae30415a2eee41a3ac45dc753d9e682f.png)
- 生成结果
![92f221b57e8c2469929f8e21e57d5dd9e20ecfdf862e9213869d4841216c65f8.png](https://mytechplayer.com/upload/2023/08/92f221b57e8c2469929f8e21e57d5dd9e20ecfdf862e9213869d4841216c65f8-bc57c13f753d409fbb976b58202ab991.png)


# My Blog
 http://mytechplayer.com/