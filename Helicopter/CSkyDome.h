#ifndef SKYDOME_H_
#define SKYDOME_H_

#ifndef PI
#define PI 3.1415926535897f
#endif

#ifndef DTOR
#define DTOR (PI/180.0f)
#endif

#ifndef SQR
#define SQR(x) (x*x)
#endif

typedef struct {
    float x, y, z;
    unsigned int color;
    float u, v;
    int   flag;
}VERTEX_SKY;

class CSkyDome
{
public:
    CSkyDome();
    ~CSkyDome();

    void GenerateDome(float radius, float dtheta, float dphi, float hTile, float vTile);
    int RenderSkyDome(float, float, float);

protected:
    void ReleaseDome();

private:
    VERTEX_SKY* Vertices;
    int NumVertices;
    float mY;
};
#endif
