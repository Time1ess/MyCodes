__metaclass__=type
import cocos

class HelloWorld(cocos.layer.Layer):
	def __init__(self):
		super(HelloWorld,self).__init__()
		label=cocos.text.Label('Hello,world',
				font_name='Times New Roman',
				font_size=32,
				anchor_x='center',anchor_y='center')
		label.position=320,240
		self.add(label)

cocos.director.director.init()
hello_layer=HelloWorld()
main_scene=cocos.scene.Scene(hello_layer)
cocos.director.director.run(main_scene)

		

