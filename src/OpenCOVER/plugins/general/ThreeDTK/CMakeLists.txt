USING(SLAM6D)
USING(GLUT)

SET(HEADERS
  ThreeDTK.h
  co3dtkDrawable.h
)
SET(SOURCES
  ThreeDTK.cpp
  co3dtkDrawable.cpp
)

ADD_DEFINITIONS(-DMAX_OPENMP_NUM_THREADS=8 -DOPENMP_NUM_THREADS=8 -DUSE_GL_POINTS)

  
cover_add_plugin(ThreeDTK)

COVISE_USE_OPENMP(ThreeDTK)
