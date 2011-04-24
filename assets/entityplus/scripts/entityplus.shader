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
// KEYCARDS 
// By Obsidian (http://robotrenegade.com)
//
models/powerups/keys/keycard-b
{
	{
		map models/powerups/keys/envmap-b.tga
		tcGen environment
		//tcMod turb 0.75 0.25 0 0.25
		//tcMod scroll 0 0.25
	}  
	{
		map models/powerups/keys/keycard-b.tga
		blendFunc blend
		rgbGen wave sin 0.5 0.25 0 0.25
	}
}
models/powerups/keys/vector-b
{
	cull none
	surfaceparm trans
	qer_trans 0.5
	{
		map models/powerups/keys/vector-b.tga
		blendFunc add
		rgbGen wave sin 0 0.5 0 0.25
	}
}
models/powerups/keys/vector-b2
{
	cull none
	surfaceparm trans
	qer_editorImage models/powerups/keys/vector-b.tga
	qer_trans 0.5
	{
		map models/powerups/keys/vector-b.tga
		blendFunc add
		rgbGen wave noise 0.75 0.25 0 30
	}
}
models/powerups/keys/vector-b3
{
	cull none
	deformVertexes move 0 0 8 sawtooth 0 1 0 2
	surfaceparm trans
	qer_editorImage models/powerups/keys/vector-b.tga
	qer_trans 0.5
	{
		map models/powerups/keys/vector-b.tga
		blendFunc add
		rgbGen wave sin 0 1 0 1
	}
}


models/powerups/keys/keycard-g
{
	{
		map models/powerups/keys/envmap-g.tga
		tcGen environment
		//tcMod turb 0.75 0.25 0 0.25
		//tcMod scroll 0 0.25
	}  
	{
		map models/powerups/keys/keycard-g.tga
		blendFunc blend
		rgbGen wave sin 0.5 0.25 0 0.25
	}
}
models/powerups/keys/vector-g
{
	cull none
	surfaceparm trans
	qer_trans 0.5
	{
		map models/powerups/keys/vector-g.tga
		blendFunc add
		rgbGen wave sin 0 0.5 0 0.25
	}
}
models/powerups/keys/vector-g2
{
	cull none
	surfaceparm trans
	qer_editorImage models/powerups/keys/vector-g.tga
	qer_trans 0.5
	{
		map models/powerups/keys/vector-g.tga
		blendFunc add
		rgbGen wave noise 0.75 0.25 0 30
	}
}
models/powerups/keys/vector-g3
{
	cull none
	deformVertexes move 0 0 8 sawtooth 0 1 0 2
	surfaceparm trans
	qer_editorImage models/powerups/keys/vector-g.tga
	qer_trans 0.5
	{
		map models/powerups/keys/vector-g.tga
		blendFunc add
		rgbGen wave sin 0 1 0 1
	}
}


models/powerups/keys/keycard-r
{
	{
		map models/powerups/keys/envmap-r.tga
		tcGen environment
		//tcMod turb 0.75 0.25 0 0.25
		//tcMod scroll 0 0.25
	}  
	{
		map models/powerups/keys/keycard-r.tga
		blendFunc blend
		rgbGen wave sin 0.5 0.25 0 0.25
	}
}
models/powerups/keys/vector-r
{
	cull none
	surfaceparm trans
	qer_trans 0.5
	{
		map models/powerups/keys/vector-r.tga
		blendFunc add
		rgbGen wave sin 0 0.5 0 0.25
	}
}
models/powerups/keys/vector-r2
{
	cull none
	surfaceparm trans
	qer_editorImage models/powerups/keys/vector-r.tga
	qer_trans 0.5
	{
		map models/powerups/keys/vector-r.tga
		blendFunc add
		rgbGen wave noise 0.75 0.25 0 30
	}
}
models/powerups/keys/vector-r3
{
	cull none
	deformVertexes move 0 0 8 sawtooth 0 1 0 2
	surfaceparm trans
	qer_editorImage models/powerups/keys/vector-r.tga
	qer_trans 0.5
	{
		map models/powerups/keys/vector-r.tga
		blendFunc add
		rgbGen wave sin 0 1 0 1
	}
}


models/powerups/keys/keycard-y
{
	{
		map models/powerups/keys/envmap-y.tga
		tcGen environment
		//tcMod turb 0.75 0.25 0 0.25
		//tcMod scroll 0 0.25
	}  
	{
		map models/powerups/keys/keycard-y.tga
		blendFunc blend
		rgbGen wave sin 0.5 0.25 0 0.25
	}
}
models/powerups/keys/vector-y
{
	cull none
	surfaceparm trans
	qer_trans 0.5
	{
		map models/powerups/keys/vector-y.tga
		blendFunc add
		rgbGen wave sin 0 0.5 0 0.25
	}
}
models/powerups/keys/vector-y2
{
	cull none
	surfaceparm trans
	qer_editorImage models/powerups/keys/vector-y.tga
	qer_trans 0.5
	{
		map models/powerups/keys/vector-y.tga
		blendFunc add
		rgbGen wave noise 0.75 0.25 0 30
	}
}
models/powerups/keys/vector-y3
{
	cull none
	deformVertexes move 0 0 8 sawtooth 0 1 0 2
	surfaceparm trans
	qer_editorImage models/powerups/keys/vector-y.tga
	qer_trans 0.5
	{
		map models/powerups/keys/vector-y.tga
		blendFunc add
		rgbGen wave sin 0 1 0 1
	}
}

//
// SKELETON KEY SHADERS
// By Hipshot (http://www.zfight.com/)
//

models/powerups/keys/key_master_snake
{
	surfaceparm trans	
	cull none	
	{
		map models/powerups/keys/key_master_snake.tga
		blendFunc add	
		tcMod scroll -1 .5
		rgbGen wave sin 0 1 0 .5	
	}

}

models/powerups/keys/key_gold_snake
{
	surfaceparm trans	
	cull none	
	qer_trans 0.5	
	{
		map models/powerups/keys/key_gold_snake.tga
		blendFunc add	
		tcMod scroll -1 .5
		rgbGen wave sin 0 1 0 .5	
	}

}

models/powerups/keys/key_silver_snake
{
	surfaceparm trans	
	cull none	
	{
		map models/powerups/keys/key_silver_snake.tga
		blendFunc add	
		tcMod scroll -1 .5
		rgbGen wave sin 0 1 0 .5	
	}

}

models/powerups/keys/key_iron_snake
{
	surfaceparm trans	
	cull none	
	{
		map models/powerups/keys/key_iron_snake.tga
		blendFunc add	
		tcMod scroll -1 .5
		rgbGen wave sin 0 1 0 .5	
	}

}

models/powerups/keys/key_master
{
	{
		map models/powerups/keys/key_master.tga
		rgbGen vertex		
	}
	{
		map models/powerups/keys/envmap-r.tga
		blendFunc add	
		tcGen environment
		rgbGen vertex
		tcMod scroll .05 .05	
		tcmod scale 2 2	
	}	
	{
		map models/powerups/keys/envmap-r.tga
		blendFunc add	
		tcGen environment
		rgbGen vertex
		tcMod scroll .05 .05	
		tcmod scale 2 2
		rgbGen wave sin 0 1 0 .5		
	}
	{
		map models/powerups/keys/key_master.tga
		blendFunc blend
		rgbGen vertex		
	}
}


models/powerups/keys/key_gold
{
	{
		map models/powerups/keys/key_gold.tga
		rgbGen vertex		
	}
	{
		map models/powerups/keys/envmap-y.tga
		blendFunc add	
		tcGen environment
		rgbGen vertex
		tcMod scroll .1 .05	
		tcmod scale 10 10
	}	
	{
		map models/powerups/keys/envmap-y.tga
		blendFunc add	
		tcGen environment
		rgbGen vertex
		tcMod scroll .1 .05	
		tcmod scale 10 10
		rgbGen wave sin 0 1 0 .5
	}	
	{
		map models/powerups/keys/key_gold.tga
		blendFunc blend
		rgbGen vertex		
	}
}

models/powerups/keys/key_silver
{
	{
		map models/powerups/keys/key_silver.tga
		rgbGen vertex		
	}
	{
		map models/powerups/keys/envmap-b.tga
		blendFunc add	
		tcGen environment
		rgbGen vertex
		tcMod scroll .05 -.05	
		tcmod scale 2 2	
	}	
	{
		map models/powerups/keys/envmap-b.tga
		blendFunc add	
		tcGen environment
		rgbGen vertex
		tcMod scroll .05 -.05	
		tcmod scale 2 2
		rgbGen wave sin 0 1 0 .5		
	}
	{
		map models/powerups/keys/key_silver.tga
		blendFunc blend
		rgbGen vertex		
	}
}

models/powerups/keys/key_iron
{
	{
		map models/powerups/keys/key_iron.tga
		rgbGen vertex		
	}
	{
		map models/powerups/keys/envmap-y.tga
		blendFunc add	
		tcGen environment
		rgbGen vertex
		tcMod scroll .1 .05	
		tcmod scale 10 10	
	}	
	{
		map models/powerups/keys/envmap-y.tga
		blendFunc add	
		tcGen environment
		rgbGen vertex
		tcMod scroll .1 .05	
		tcmod scale 10 10
		rgbGen wave sin 0 1 0 .5		
	}
	{
		map models/powerups/keys/key_iron.tga
		blendFunc blend
		rgbGen vertex		
	}
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