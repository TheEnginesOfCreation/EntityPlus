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
      map models/powerups/keys/key_gold.tga
      rgbGen lightingDiffuse      
   }
   {
      map models/powerups/keys/envmap-r.tga
      blendFunc add         
      tcGen environment
      rgbGen lightingDiffuse
      tcMod scroll .05 .05
      tcmod scale 2 2
   }
   {
      map models/powerups/keys/envmap-r.tga
      blendFunc add
      tcGen environment
      tcMod scroll .05 .05
      tcmod scale 2 2
      rgbGen wave sin 0 1 0 .5
   }
   {
      map models/powerups/keys/key_master.tga
      blendFunc blend
      rgbGen lightingDiffuse
   }
}

models/powerups/keys/key_gold
{
   {
      map models/powerups/keys/key_gold.tga
      rgbGen lightingDiffuse      
   }
   {
      map models/powerups/keys/envmap-y.tga
      blendFunc add      
      tcGen environment
      rgbGen lightingDiffuse
      tcMod scroll .05 .05
      tcmod scale 2 2
   }
   {
      map models/powerups/keys/envmap-y.tga
      blendFunc add
      tcGen environment
      tcMod scroll .05 .05
      tcmod scale 2 2
      rgbGen wave sin 0 1 0 .5
   }
   {
      map models/powerups/keys/key_gold.tga
      blendFunc blend
      rgbGen lightingDiffuse
   }
}

models/powerups/keys/key_silver
{
   {
      map models/powerups/keys/key_silver.tga
      rgbGen lightingDiffuse      
   }
   {
      map models/powerups/keys/envmap-b.tga
      blendFunc add      
      tcGen environment
      rgbGen lightingDiffuse
      tcMod scroll .05 .05
      tcmod scale 2 2
   }
   {
      map models/powerups/keys/envmap-b.tga
      blendFunc add
      tcGen environment
      tcMod scroll .05 .05
      tcmod scale 2 2
      rgbGen wave sin 0 1 0 .5
   }
   {
      map models/powerups/keys/key_silver.tga
      blendFunc blend
      rgbGen lightingDiffuse
   }
}

models/powerups/keys/key_iron
{
   {
      map models/powerups/keys/key_iron.tga
      rgbGen lightingDiffuse      
   }
   {
      map models/powerups/keys/envmap-y.tga
      blendFunc add         
      tcGen environment
      rgbGen lightingDiffuse
      tcMod scroll .05 .05
      tcmod scale 2 2
   }
   {
      map models/powerups/keys/envmap-y.tga
      blendFunc add
      tcGen environment
      tcMod scroll .05 .05
      tcmod scale 2 2
      rgbGen wave sin 0 1 0 .5
   }
   {
      map models/powerups/keys/key_iron.tga
      blendFunc blend
      rgbGen lightingDiffuse
   }
}

//
// SHRUNK LIGHTNING GUN
//
lightningBoltNew_medium
{
	cull none
	{
		map gfx/misc/lightning3new_medium.tga
		blendFunc GL_ONE GL_ONE
		rgbgen wave sin 1 0.5 0 7.1
		tcmod scale  2 1
		tcMod scroll -5 0
	}
	{
		map gfx/misc/lightning3new_medium.tga
		blendFunc GL_ONE GL_ONE
		rgbgen wave sin 1 0.8 0 8.1
		tcmod scale  -1.3 -1
		tcMod scroll -7.2 0
	}
}

lightningBoltNew_small
{
	cull none
	{
		map gfx/misc/lightning3new_small.tga
		blendFunc GL_ONE GL_ONE
		rgbgen wave sin 1 0.5 0 7.1
		tcmod scale  2 1
		tcMod scroll -5 0
	}
	{
		map gfx/misc/lightning3new_small.tga
		blendFunc GL_ONE GL_ONE
		rgbgen wave sin 1 0.8 0 8.1
		tcmod scale  -1.3 -1
		tcMod scroll -7.2 0
	}
}

//
// GLASS DEBRIS
//
models/debris/glass
{
	{
		map textures/effects/envmap2.tga
		blendfunc add
		tcGen environment 
	}
}

//
// PARTICLE EFFECTS
//
spark
{
	cull none
	entityMergable
	{
		map gfx/misc/spark.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen		vertex
		alphaGen	vertex
	}
}

//
// PAINTBALL MODE WALLMARKS
//
gfx/damage/bullet_mrk_paint
{
	polygonOffset
	{
		map gfx/damage/bullet_mrk_paint.tga
		blendFunc add
		rgbGen exactVertex
	}
}

gfx/damage/burn_med_mrk_paint
{
	polygonOffset
	{
		map gfx/damage/burn_med_mrk_paint.tga
		blendFunc add
		rgbGen exactVertex
	}
}

gfx/damage/hole_lg_mrk_paint
{
	polygonOffset
	{
		map gfx/damage/hole_lg_mrk_paint.tga
		blendFunc add
		rgbGen exactVertex
	}
}

gfx/damage/plasma_mrk_paint
{
	polygonOffset
	{
		map gfx/damage/plasma_mrk_paint.tga
		blendFunc add
		rgbGen exactVertex
	}
}

//
// MENU SHADERS
//

menu/backgrounds/01
{
	{
		map menu/backgrounds/01.tga
	}
	{
		map menu/backgrounds/02.tga
		blendFunc blend
		alphaGen wave sin 0 1 0.5 .1
	}
	//{
	//	map menu/art/logo2.tga
	//	blendFunc blend
	//}
}

menu/art/loading
{
	{
		map menu/art/loading.tga
		tcMod rotate 360
	}
}

//
// MENU LOGO MODEL SHADERS
//
// Obsidian @ RobotRenegade.com 2011
models/entplus/logo/materials/plusg
{
	cull none
	{
		map models/entplus/logo/materials/plusg.tga
		//alphaFunc GE128
		blendFunc blend
	}
}