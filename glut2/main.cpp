#include <stdio.h>
#include <glew.h>
#include <gl/glut.h>

GLuint eboID;

#define USE_EBO 

GLfloat vertices[] = {
    0.5f, 0.5f, 0.0f,   // ���Ͻ�
    0.5f, -0.5f, 0.0f,  // ���½�
    -0.5f, -0.5f, 0.0f, // ���½�
    -0.5f, 0.5f, 0.0f   // ���Ͻ�
};

GLuint indices[] = {
    // ��ʼ��0!
    0, 1, 3, // ��һ��������
    1, 2, 3  // �ڶ���������
};


void ChangeSize(int w, int h)
{
    if (h == 0)
        h = 1;
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, w*1.0 / h, 0.01, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void SetupRC()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glGenBuffers(1, &eboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glLoadIdentity();
    glTranslatef(0, 0, -5.0);

    //����VA״̬  
    glEnableClientState(GL_VERTEX_ARRAY);

    //������  
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    //����

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    //�ر�VA״̬  
    glDisableClientState(GL_VERTEX_ARRAY);

    glutSwapBuffers();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}


int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL");
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);

    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
        return 1;
    }

    SetupRC();

    glutMainLoop();
    return 0;
}