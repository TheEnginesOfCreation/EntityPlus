//
// EP_EXAMPLE.MAP
//

textures/ep_example/lavahelldark
{
	qer_editorimage textures/liquids/lavahell.tga
	q3map_globaltexture
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm noimpact
	surfaceparm nolightmap
	q3map_surfacelight 150
	cull disable

	tesssize 128
	cull disable
	deformVertexes wave 100 sin 3 2 .1 0.1
	
	{
		map textures/liquids/lavahell.tga
		tcMod turb 0 .2 0 .1
	}
}


textures/ep_example/timbutton01
{
	qer_editorimage textures/gothic_button/timbutton.tga
	q3map_lightimage textures/gothic_button/timbutton2.tga
	q3map_surfacelight 10
	//light 1

	{
		map textures/gothic_button/timbutton.tga
	}


	{
		map $lightmap
		blendfunc gl_dst_color gl_zero
		rgbgen identity
	}

	{
		map textures/gothic_button/timbutton2.tga
		blendfunc gl_one gl_one
		rgbgen wave sin .5 .5 0 1
	}

}

textures/ep_example/timbutton02
{
	qer_editorimage textures/gothic_button/timbutton.tga
	q3map_lightimage textures/gothic_button/timbutton2.tga
	q3map_surfacelight 10
	//light 1

	{
		map textures/gothic_button/timbutton.tga
	}


	{
		map $lightmap
		blendfunc gl_dst_color gl_zero
		rgbgen identity
	}

	{
		map textures/gothic_button/timbutton2.tga
		blendfunc gl_one gl_one
		rgbgen wave sin .5 .5 0 1
	}

}

textures/ep_example/timbutton03
{
	qer_editorimage textures/gothic_button/timbutton.tga
	q3map_lightimage textures/gothic_button/timbutton2.tga
	q3map_surfacelight 10
	//light 1

	{
		map textures/gothic_button/timbutton.tga
	}


	{
		map $lightmap
		blendfunc gl_dst_color gl_zero
		rgbgen identity
	}

	{
		map textures/gothic_button/timbutton2.tga
		blendfunc gl_one gl_one
		rgbgen wave sin .5 .5 0 1
	}

}

textures/ep_example/timbutton04
{
	qer_editorimage textures/gothic_button/timbutton.tga
	q3map_lightimage textures/gothic_button/timbutton2.tga
	q3map_surfacelight 10
	//light 1

	{
		map textures/gothic_button/timbutton.tga
	}


	{
		map $lightmap
		blendfunc gl_dst_color gl_zero
		rgbgen identity
	}

	{
		map textures/gothic_button/timbutton2.tga
		blendfunc gl_one gl_one
		rgbgen wave sin .5 .5 0 1
	}

}

textures/ep_example/timbutton_off
{
	qer_editorimage textures/gothic_button/timbutton.tga
	q3map_lightimage textures/gothic_button/timbutton2.tga
	q3map_surfacelight 10
	//light 1

	{
		map textures/gothic_button/timbutton.tga
	}


	{
		map $lightmap
		blendfunc gl_dst_color gl_zero
		rgbgen identity
	}

}