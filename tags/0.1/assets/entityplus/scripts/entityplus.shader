textures/entityplus/dirt
{
	qer_editorimage textures/organics/dirt2.tga
	surfaceparm trans
	{
		map $lightmap
		rgbGen identity
	}
	{
		map textures/organics/dirt2.tga
		rgbGen identity
	}
}

textures/entityplus/target_logic
{
	qer_editorimage textures/entityplus/target_logic.tga
	qer_trans .5
	surfaceparm nomarks
	surfaceparm trans
	surfaceparm nonsolid
	cull disable
	{
		map textures/entityplus/target_logic.tga
		blendfunc add
		rgbgen identity
	}
	{
		map textures/entityplus/screen_noise.tga
		blendfunc add
		rgbgen wave triangle .5 .05 0 10
		tcmod scroll 5 .25 
	}	
}

textures/entityplus/target_gravity
{
	qer_editorimage textures/entityplus/target_gravity.tga
	qer_trans .5
	surfaceparm nomarks
	surfaceparm trans
	surfaceparm nonsolid
	cull disable
	{
		map textures/entityplus/target_gravity.tga
		blendfunc add
		rgbgen identity
	}
	{
		map textures/entityplus/screen_noise.tga
		blendfunc add
		rgbgen wave triangle .5 .05 0 10
		tcmod scroll 5 .25 
	}	
}

textures/entityplus/func_breakable
{
	qer_editorimage textures/entityplus/func_breakable.tga
	qer_trans .5
	surfaceparm nomarks
	surfaceparm trans
	surfaceparm nonsolid
	cull disable
	{
		map textures/entityplus/func_breakable.tga
		blendfunc add
		rgbgen identity
	}
	{
		map textures/entityplus/screen_noise.tga
		blendfunc add
		rgbgen wave triangle .5 .05 0 10
		tcmod scroll 5 .25 
	}	
}

textures/entityplus/target_intermission
{
	qer_editorimage textures/entityplus/target_intermission.tga
	qer_trans .5
	surfaceparm nomarks
	surfaceparm trans
	surfaceparm nonsolid
	cull disable
	{
		map textures/entityplus/target_intermission.tga
		blendfunc add
		rgbgen identity
	}
	{
		map textures/entityplus/screen_noise.tga
		blendfunc add
		rgbgen wave triangle .5 .05 0 10
		tcmod scroll 5 .25 
	}	
}