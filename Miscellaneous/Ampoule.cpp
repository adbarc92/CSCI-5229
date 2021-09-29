void ampoule(int amp){

  glDisable(GL_BLEND);
  // Cylinder Cap - Gold
  glPushMatrix();
  glTranslated(0,1.5,0);
  glScaled(0.78,0.20,0.78);
  glColor3f(VEC3DARGS(getColor("gold")));
  cylinder(""); // case 1 end
  glPopMatrix();

  // Cylinder Bottom - Gold
  glPushMatrix();
  glTranslated(0,-1.5,0);
  glScaled(0.78,0.20,0.78);
  glColor3f(VEC3DARGS(getColor("gold")));
  cylinder(""); // case 2 end
  glPopMatrix();

  // Cylinder Bottom
  glPushMatrix();
  glTranslated(0,-1.8,0);
  glScaled(0.6,0.20,0.6);
  glColor3f(VEC3DARGS(getColor("gold")));
  cylinder(""); // case 2 end
  glPopMatrix();

  // Handle, Large Prong
  glPushMatrix();
  glTranslated(0,2,0);
  glScaled(0.18,0.25,0.12);
  glColor3f(VEC3DARGS(getColor("gold")));
  cube("");
  glPopMatrix();

  // Handle, Small Prong, Right
  glPushMatrix();
  glTranslated(0.5,2,0);
  glScaled(0.09,0.3,0.09);
  glColor3f(VEC3DARGS(getColor("gold")));
  cube("");
  glPopMatrix();

  // Handle, Small Prong, Left
  glPushMatrix();
  glTranslated(-0.5,2,0);
  glScaled(0.09,0.28,0.09);
  glColor3f(VEC3DARGS(getColor("gold")));
  cube("");
  glPopMatrix();

  // Handle, Sphere
  glPushMatrix();
  glTranslated(0,2.3,0);
  glScaled(0.15,0.15,0.15);
  glColor3f(VEC3DARGS(getColor("gold")));
  sphere("");
  glPopMatrix();

  // Handle, Top Cylinder
  glPushMatrix();
  glTranslated(0,2.95,0);
  glScaled(0.15,0.5,0.15);
  glColor3f(VEC3DARGS(getColor("gold")));
  cylinder("");
  glPopMatrix();

  // Handle, Small Prong, Right, Connector
  glPushMatrix();
  glTranslated(-0.3,2.1,0);
  glRotated(90,0,0,1);
  glScaled(0.05,0.15,0.05);
  glColor3f(VEC3DARGS(getColor("gold")));
  cube("");
  glPopMatrix();

  // Handle, Small Prong, Left, Connector
  glPushMatrix();
  glTranslated(0.3,2.1,0);
  glRotated(90,0,0,1);
  glScaled(0.05,0.15,0.05);
  glColor3f(VEC3DARGS(getColor("gold")));
  cube("");
  glPopMatrix();

  // Inner Cylinder, Top
  glPushMatrix();
  glTranslated(0,1.3,0);
  glScaled(0.1,0.6,0.1);
  glColor3f(VEC3DARGS(getColor("gold")));
  cylinder("");
  glPopMatrix();

  // Inner Cone
  glPushMatrix();
  glTranslated(0,0.5,0);
  glScaled(0.4,0.4,0.4);
  glColor3f(VEC3DARGS(getColor("gold")));
  cone("");
  glPopMatrix();

  // Inner Cylinder, Bottom
  glPushMatrix();
  glTranslated(0,-1.3,0);
  glScaled(0.1,0.4,0.1);
  glColor3f(VEC3DARGS(getColor("gold")));
  cylinder("");
  glPopMatrix();

  // Inner Cylinder, Bottom, Wide
  glPushMatrix();
  glTranslated(0,-0.9,0);
  glScaled(0.4,0.05,0.4);
  glColor3f(VEC3DARGS(getColor("gold")));
  cylinder("");
  glPopMatrix();

  // Inner Cylinder, 2nd Bottom, Wide
  glPushMatrix();
  glTranslated(0,-0.7,0);
  glScaled(0.4,0.05,0.4);
  glColor3f(VEC3DARGS(getColor("gold")));
  cylinder("");
  glPopMatrix();

  // Inner Prongs, 1-4
  glPushMatrix();
  glTranslated(0,-0.65,0.3);
  glScaled(0.05,0.2,0.05);
  glColor3f(VEC3DARGS(getColor("gold")));
  cylinder("");
  glPopMatrix();

  glPushMatrix();
  glTranslated(0,-0.65,-0.3);
  glScaled(0.05,0.2,0.05);
  glColor3f(VEC3DARGS(getColor("gold")));
  cylinder("");
  glPopMatrix();

  glPushMatrix();
  glTranslated(0.3,-0.65,0);
  glScaled(0.05,0.2,0.05);
  glColor3f(VEC3DARGS(getColor("gold")));
  cylinder("");
  glPopMatrix();

  glPushMatrix();
  glTranslated(-0.3,-0.65,0);
  glScaled(0.05,0.2,0.05);
  glColor3f(VEC3DARGS(getColor("gold")));
  cylinder("");
  glPopMatrix();

  // Inner Prong Spheres
  glPushMatrix();
  glTranslated(0,-0.4,0.3);
  glScaled(0.06,0.06,0.06);
  glColor3f(VEC3DARGS(getColor("gold")));
  sphere("");
  glPopMatrix();

  glPushMatrix();
  glTranslated(0,-0.4,-0.3);
  glScaled(0.06,0.06,0.06);
  glColor3f(VEC3DARGS(getColor("gold")));
  sphere("");
  glPopMatrix();

  glPushMatrix();
  glTranslated(0.3,-0.4,0);
  glScaled(0.06,0.06,0.06);
  glColor3f(VEC3DARGS(getColor("gold")));
  sphere("");
  glPopMatrix();

  glPushMatrix();
  glTranslated(-0.3,-0.4,0);
  glScaled(0.06,0.06,0.06);
  glColor3f(VEC3DARGS(getColor("gold")));
  sphere("");
  glPopMatrix();

  // Inner Sphere
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE);
  glPushMatrix();
  glTranslated(0,0,0);
  glScaled(0.06*3,0.06*3,0.06*3);
  glColor3f(VEC3DARGS(getColor("darkblue")));
  sphere("");
  glPopMatrix();
  glDisable(GL_BLEND);

  // Socket Prong 1: Left
  glPushMatrix();
  glTranslated(0.3,-2,0);
  glRotated(90,0,0,1);
  glScaled(0.15,0.15,0.15);
  glColor3f(VEC3DARGS(getColor("gold")));
  wing("");
  glPopMatrix();

  // Socket Prong 2: Right
  glPushMatrix();
  glTranslated(-0.3,-2,0);
  glRotated(90,0,0,1);
  glScaled(0.15,0.15,0.15);
  glColor3f(VEC3DARGS(getColor("gold")));
  wing("");
  glPopMatrix();

  // Socket Prong 3: Center
  glPushMatrix();
  glTranslated(0,-2,0);
  glRotated(90,0,0,1);
  glScaled(0.2,0.2,0.2);
  glColor3f(VEC3DARGS(getColor("gold")));
  wing("");
  glPopMatrix();

  // Rectangular Cover, Top
    // glPushMatrix();
    // glPopMatrix();

  // Rectangular Cover, Bottom
    // glPushMatrix();
    // glPopMatrix();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE);

  // Cylinder, Main
  glPushMatrix();
  glScaled(0.8,1.35,0.8);
  glColor4f(0,0,1,0.01*100); // Blue
  cylinder(""); // case 0 end
  glPopMatrix();
  
  glDisable(GL_BLEND);
}