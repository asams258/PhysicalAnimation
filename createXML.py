import subprocess;

outDir = '/Users/arthur/Desktop/SPHRender/XML/'
filePath = '/Users/arthur/Desktop/SPHRender/locs.txt'

def beginScene():
    return '<scene version="0.5.0">\n'\
            '<!-- Instantiate a unidirectional path tracer,\n'\
            'which renders paths up to a depth of 3 -->\n'\
            '<integrator type="path">\n'\
            '<integer name="maxDepth" value="3"/>\n'\
            '</integrator>\n'

def addParticle(x,y,z):
  return '<shape type="sphere">\n'\
         '<point name="center" x="'+x+'" y="'+y+'" z="'+z+'"/> <float name="radius" value=".015"/>\n'\
         '<bsdf type="diffuse"/>\n'\
         '</shape>\n\n'

def addSensor():
  return '<sensor type = "perspective">\n'\
         '<float name="fov" value="60"/>\n'\
         '<transform name ="toWorld">\n'\
         '<lookat origin="3, 1, 3" target="5, 1, 5" up ="0, 1, 0"/> \n'\
         '</transform>\n'\
         '</sensor>\n\n'

def endScene():
  return '</scene>'

def process():
    i = 0
    data = []
    scene = ''
    #open our location file
    posts = open(filePath,'r')
    #toss out first line
    posts.readline()
    scene += beginScene()
    scene += addSensor() 
    for line in posts:
        #write the last time series
        if (line.startswith('Time')):
            scene += endScene()
            name = 'out'+str(i).zfill(6)+'.xml'
            xml = open(outDir+name,'w')
            xml.write(scene)
            xml.close()
            #reset scene accum and increase scene ct
            scene = ''
            scene += beginScene()
            scene += addSensor()
            i+=1
        #otherwise process particles
        else:
            data = line.split()
            scene += addParticle(data[0],data[1],data[2])
    #close the last Set
    scene += endScene()
    name = 'out'+str(i).zfill(6)+'.xml'
    xml = open(outDir+name,'w')
    xml.write(scene)
    xml.close()

def main():
    process()
    #add in mitsuba subprocess?
    #add in animate subprocess? ffmpeg?
    subprocess.call('mitsuba XML/out*.xml', shell=True)
    #can add exr to png conversion
    subprocess.call('ffmpeg -r 96 -i XML/out%06d.exr  -vb 20M -r 96 myvideo.mpg', shell=True)

if __name__ =='__main__':
    main()

