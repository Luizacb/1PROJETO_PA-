#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "sculptor.h"

Sculptor::Sculptor(int _nx, int _ny, int _nz){
    nx = _nx;
    ny = _ny;
    nz = _nz;

    v = (Voxel***) malloc(nx * sizeof(Voxel));

    for (int x = 0; x < nx; x++){
        v[x] = (Voxel**) malloc(ny * sizeof(Voxel));
    }

    for (int x = 0; x < nx; x++){
            for (int y = 0; y < ny; y++){
                v[x][y] = (Voxel*) malloc(nz * sizeof(Voxel));
            }
    }

    //set all voxels to false
    for (int x = 0; x < nx; x++){
        for (int y = 0; y <ny; y++){
            for (int z = 0; z < nz; z++){
                Sculptor::cutVoxel(x, y, z);
            }
        }
    }
  };


  

  Sculptor::~Sculptor(){
    for (int x = 0; x < nx; x++){
        for (int y = 0; y < ny; y++){
            free(v[x][y]);
        }
    }

    for (int x = 0; x < nx; x++){
        free(v[x]);
    }

    free(v);
  };

  void Sculptor::setColor(float _r, float _g, float _b, float _a){
    r = _r;
    g = _g;
    b = _b;
    a = _a;
    };

  void Sculptor::putVoxel(int x, int y, int z){
    if (x < 0 || x >= nx || y < 0 || y >= ny || z < 0 || z >= nz){
        std::cout << "Coordenadas invalidas! " << x << ", " << y << ", " << z << std::endl;
        return;
    }
    v[x][y][z].r = r;
    v[x][y][z].g = g;
    v[x][y][z].b = b;
    v[x][y][z].a = a;
    v[x][y][z].show = true;
  };

  void Sculptor::cutVoxel(int x, int y, int z){
    v[x][y][z].show = false;
  };

  void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
    for (int x = x0; x < x1; x++){
        for (int y = y0; y < y1; y++){
            for (int z = z0; z < z1; z++){
                Sculptor::putVoxel(x, y, z);
            }
        }
    }
};

  void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
    for (int x = x0; x < x1; x++){
        for (int y = y0; y < y1; y++){
                for (int z = z0; z < z1; z++){
                Sculptor::cutVoxel(x, y, z);
            }
        }
    }
};

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius){
    int xmin, xmax, ymin, ymax, zmin, zmax;
    if (xcenter - radius >0){xmin = xcenter - radius;} 
    else {xmin = 0;}

    if (xcenter + radius < nx){xmax = xcenter + radius;}
    else {xmax = nx-1;}

    if (ycenter - radius >0){ymin = ycenter - radius;} 
    else {ymin = 0;}

    if (ycenter + radius < ny){ymax = ycenter + radius;}
    else {ymax = ny-1;}

    if (zcenter - radius >0){zmin = zcenter - radius;} 
    else {zmin = 0;}

    if (zcenter + radius < nz){zmax = zcenter + radius;}
    else {zmax = nz-1;}

    for (int x = xmin; x < xmax; x++){
        for (int y = ymin; y < ymax; y++){
            for (int z = zmin; z < zmax; z++){
                
                if((x - xcenter)*(x - xcenter) + (y - ycenter)*(y - ycenter) + (z - zcenter)*(z - zcenter) < radius*radius){
                    Sculptor::putVoxel(x, y, z);
                }
            }
        }
    }
};

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius){
    int xmin, xmax, ymin, ymax, zmin, zmax;
    if (xcenter - radius >=0){xmin = xcenter - radius;} 
    else {xmin = 0;}

    if (xcenter + radius <= nx){xmax = xcenter + radius;}
    else {xmax = nx-1;}

    if (ycenter - radius >=0){ymin = ycenter - radius;} 
    else {ymin = 0;}

    if (ycenter + radius <= ny){ymax = ycenter + radius;}
    else {ymax = ny-1;}

    if (zcenter - radius >=0){zmin = zcenter - radius;} 
    else {zmin = 0;}

    if (zcenter + radius <= nz){zmax = zcenter + radius;}
    else {zmax = nz-1;}

    for (int x = xmin; x <= xmax; x++){
        for (int y = ymin; y <= ymax; y++){
            for (int z = zmin; z <= zmax; z++){
                
                if((x - xcenter)*(x - xcenter) + (y - ycenter)*(y - ycenter) + (z - zcenter)*(z - zcenter) <= radius*radius){
                    Sculptor::cutVoxel(x, y, z);
                }
            }
        }
    }
};

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    int xmin, xmax, ymin, ymax, zmin, zmax;
    if (xcenter - rx >=0){xmin = xcenter - rx;} 
    else {xmin = 0;}

    if (xcenter + rx < nx){xmax = xcenter + rx;}
    else {xmax = nx-1;}

    if (ycenter - ry >=0){ymin = ycenter - ry;} 
    else {ymin = 0;}

    if (ycenter + ry < ny){ymax = ycenter + ry;}
    else {ymax = ny-1;}

    if (zcenter - rz >=0){zmin = zcenter - rz;} 
    else {zmin = 0;}

    if (zcenter + rz < nz){zmax = zcenter + rz;}
    else {zmax = nz-1;}

    for (int x = xmin; x <= xmax; x++){
        for (int y = ymin; y <= ymax; y++){
            for (int z = zmin; z <= zmax; z++){
                
                if((((float)(x - xcenter)*(x - xcenter))/(rx*rx)) + (((float)(y - ycenter)*(y - ycenter))/(ry*ry)) + (((float)(z - zcenter)*(z - zcenter))/(rz*rz)) <= 1){
                    Sculptor::putVoxel(x, y, z);
                }
            }
        }
    }
};

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    int xmin, xmax, ymin, ymax, zmin, zmax;
    if (xcenter - rx >=0){xmin = xcenter - rx;} 
    else {xmin = 0;}

    if (xcenter + rx < nx){xmax = xcenter + rx;}
    else {xmax = nx-1;}

    if (ycenter - ry >=0){ymin = ycenter - ry;} 
    else {ymin = 0;}

    if (ycenter + ry < ny){ymax = ycenter + ry;}
    else {ymax = ny-1;}

    if (zcenter - rz >=0){zmin = zcenter - rz;} 
    else {zmin = 0;}

    if (zcenter + rz < nz){zmax = zcenter + rz;}
    else {zmax = nz-1;}

    for (int x = xmin; x <= xmax; x++){
        for (int y = ymin; y <= ymax; y++){
            for (int z = zmin; z <= zmax; z++){
                
                if(((float)(x - xcenter)*(x - xcenter))/(rx*rx) + ((float)(y - ycenter)*(y - ycenter))/(ry*ry) + ((float)(z - zcenter)*(z - zcenter))/(rz*rz) <= 1){
                    Sculptor::cutVoxel(x, y, z);
                }
            }
        }
    }
};

void Sculptor::writeOFF(const char* filename){
    std::ofstream of;

    of.open(filename, std::ios_base::trunc);

    int nvoxels = 0;
    for (int i = 0; i < nx; i++){
        for (int j = 0; j < ny; j++){
            for (int k = 0; k < nz; k++){
                if (v[i][j][k].show == true){
                    nvoxels++;
                }
            }
        }
    }

    of << "OFF" << std::endl;
    of << 8*nvoxels << " " << 6*nvoxels << " " << 0 << std::endl;

    for (int i = 0; i < nx; i++){
        for (int j = 0; j < ny; j++){
            for (int k = 0; k < nz; k++){
                if (v[i][j][k].show == true){
                of << -0.5+i << " " << 0.5+j << " " << -0.5+k << std::endl;
                of << -0.5+i << " " << -0.5+j << " " << -0.5+k << std::endl;
                of << 0.5+i << " " << -0.5+j << " " << -0.5+k << std::endl;
                of << 0.5+i << " " << 0.5+j << " " << -0.5+k << std::endl;
                of << -0.5+i << " " << 0.5+j << " " << 0.5+k << std::endl;
                of << -0.5+i << " " << -0.5+j << " " << 0.5+k << std::endl;
                of << 0.5+i << " " << -0.5+j << " " << 0.5+k << std::endl;
                of << 0.5+i << " " << 0.5+j << " " << 0.5+k << std::endl;
                }
            }
        }
    }

    std::string _r, _g, _b;
    int nvertice = 0;
    for (int i = 0; i < nx; i++){
        for (int j = 0; j < ny; j++){
            for (int k = 0; k < nz; k++){
                if (v[i][j][k].show == true){

                    if (v[i][j][k].r == 1){_r = "1.0";}
                    if (v[i][j][k].r == 0){_r = "0.0";}
                    else {_r = std::to_string(v[i][j][k].r);}

                    if (v[i][j][k].g == 1){_g = "1.0";}
                    if (v[i][j][k].g == 0){_g = "0.0";}
                    else {_g = std::to_string(v[i][j][k].g);}

                    if (v[i][j][k].b == 1){_b = "1.0";}
                    if (v[i][j][k].b == 0){_b = "0.0";}
                    else {_b = std::to_string(v[i][j][k].b);}

                    of << 4 << " " << nvertice+0 << " " << nvertice+3 << " " << nvertice+2 << " " << nvertice+1 << " " << _r << " " << _g << " " << _b << " " << a << std::endl;
                    of << 4 << " " << nvertice+4 << " " << nvertice+5 << " " << nvertice+6 << " " << nvertice+7 << " " << _r << " " << _g << " " << _b << " " << a << std::endl;
                    of << 4 << " " << nvertice+0 << " " << nvertice+1 << " " << nvertice+5 << " " << nvertice+4 << " " << _r << " " << _g << " " << _b << " " << a << std::endl;
                    of << 4 << " " << nvertice+0 << " " << nvertice+4 << " " << nvertice+7 << " " << nvertice+3 << " " << _r << " " << _g << " " << _b << " " << a << std::endl;
                    of << 4 << " " << nvertice+7 << " " << nvertice+6 << " " << nvertice+2 << " " << nvertice+3 << " " << _r << " " << _g << " " << _b << " " << a << std::endl;
                    of << 4 << " " << nvertice+1 << " " << nvertice+2 << " " << nvertice+6 << " " << nvertice+5 << " " << _r << " " << _g << " " << _b << " " << a << std::endl;
                    nvertice += 8;
                }
            }
        }
    }

of.close();
}