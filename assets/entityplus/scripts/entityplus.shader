//
// ITEM_ARMOR_VEST
//

models/powerups/armor/newgreen
{      
	{
		map textures/sfx/specular.tga
		tcGen environment
		rgbGen identity
	}
	{
		map models/powerups/armor/newgreen.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen identity
	}
}

models/powerups/armor/energy_gre1
{
	{
		map models/powerups/armor/energy_gre1.tga 
		blendFunc GL_ONE GL_ONE
		tcMod scroll 7.4 1.3
	}
}

//
// LADDERCLIP
//
textures/common/ladderclip
{
	qer_trans 0.40
	surfaceparm nolightmap
	surfaceparm nomarks
	surfaceparm nodraw
	surfaceparm nonsolid
	surfaceparm playerclip
	surfaceparm noimpact
	surfaceparm ladder
}

//
// ENTITYPLUS.MAP
//

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

textures/entityplus/target_disable
{
	qer_editorimage textures/entityplus/target_disable.tga
	qer_trans .5
	surfaceparm nomarks
	surfaceparm trans
	surfaceparm nonsolid
	cull disable
	{
		map textures/entityplus/target_disable.tga
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

textures/entityplus/target_botspawn
{
	qer_editorimage textures/entityplus/target_botspawn.tga
	qer_trans .5
	surfaceparm nomarks
	surfaceparm trans
	surfaceparm nonsolid
	cull disable
	{
		map textures/entityplus/target_botspawn.tga
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

textures/entityplus/target_playerspeed
{
	qer_editorimage textures/entityplus/target_playerspeed.tga
	qer_trans .5
	surfaceparm nomarks
	surfaceparm trans
	surfaceparm nonsolid
	cull disable
	{
		map textures/entityplus/target_playerspeed.tga
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

textures/entityplus/bouncepad1q1metal7_99_disabled
{
	surfaceparm nodamage
	q3map_lightimage textures/sfx/jumppadsmall.tga	
	q3map_surfacelight 2000
	qer_editorimage textures/sfx/bouncepad1q1metal7_99.tga

	
	{
		map textures/sfx/bouncepad1q1metal7_99.tga
		rgbGen identity
	}
	
	{
		map $lightmap
		rgbGen identity
		blendfunc gl_dst_color gl_zero
	}
}