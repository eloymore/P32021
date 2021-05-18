local mapa = {
  ambient="0.1,0.1,0.1",
  gravity="0 -9.8 0",
  entities={
    { 
      name="Sinbad",
      id=1,
      components={
        transform={
          position="0,0,0",
          rotation="0,0,0",
          scale="10,10,10"
        },
        renderer={
          mesh="Sinbad.mesh",
          material="",
          visible="true"
        },
        rigidbody={
          shape="-1",
          mass="54",
          inertia="0,0,0",
          restitution="0.2",
          damping="0.2,0.2",
          trigger="false"
        },
        lifetime={
          life="5",
          year="2021"
        }
      }
    },
    {
      name="Camera",
      id=2,
      components={
        transform={
          position="0,0,100",
          rotation="0,0,0",
          scale="1,1,1"
        },
        camera={
          near="0.1",
          far="1000",
          autoaspect="true",
          aspect="1.78",
          fov="50",
          proyection="0",
          viewport="0,0,1,1",
          color="1.0,0.5,0.3137"
        }
      }
    },
    {
    name="Luz",
    id=3,
    components={
      transform={
        position="50,0,0",
        rotation="0,0,0",
        scale="1,1,1"
      },
      light={
        type="0",
        attenuation="",
        shadows="true",
        diffuse="1,0.2,1,1",
        specular="1,1,1,1",
        spotinner="",
        spotouter=""
        }
      }
    },
    {
    	name="Boton",
    	id=4,
    	components={
        button={
          text="Salir",
          position="0.5,0.5",
          size="10,10",
          name="botonSalir",
          type="EXIT",
          nextScene=""
        }   	
    	},
    }
  }
}

function GetMapa ()
  return mapa
end

