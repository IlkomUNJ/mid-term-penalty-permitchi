#include "drawingcanvas.h"
#include "Patterns.h"

DrawingCanvas::DrawingCanvas(QWidget *parent)  {
    // Set a minimum size for the canvas
    setMinimumSize(this->WINDOW_WIDTH, this->WINDOW_HEIGHT);
    // Set a solid background color
    setStyleSheet("background-color: white; border: 1px solid gray;");
}

void DrawingCanvas::clearPoints(){
    m_points.clear();
    // Trigger a repaint to clear the canvas
    update();
}

void DrawingCanvas::paintLines(){
    /* Todo
     * Implement lines drawing per even pair
    */

    isPaintLinesClicked = true;
    update();
}

void DrawingCanvas::segmentDetection(){
    QPixmap pixmap = this->grab(); //
    QImage image = pixmap.toImage();

    //misunderstood the assignment and spent way too long on this yay :^)
    // QVector<QPoint> segmentPoints = m_points;
    // QRect boundingBox;

    // for (const QPoint& p : m_points) {
    //     boundingBox = boundingBox.united(QRect(p, QSize(1, 1)));
    // }

    // // The QRect now represents the bounding box
    // int minX = boundingBox.left();
    // int maxX = boundingBox.right();
    // int minY = boundingBox.top();
    // int maxY = boundingBox.bottom();


    // qDebug() << "Min X:" << minX << "Max X:" << maxX;
    // qDebug() << "Min Y:" << minY << "Max Y:" << maxY;

    // qDebug() << "List size:" << segmentPoints.size();
    // for (const QPoint& p : segmentPoints) {
    //     qDebug() << "Point (" << p.x() << "," << p.y() << ")";
    // }
    // cout << "image width " << maxX - minX << endl;
    // cout << "image height " << maxY - minY << endl;


    cout << "image width " << image.width() << endl;
    cout << "image height " << image.height() << endl;

    //To not crash we set initial size of the matrix
    vector<CustomMatrix> windows(image.width()*image.height());
    std::string feature_type = "None";

    // Get the pixel value as an ARGB integer (QRgb is a typedef for unsigned int)
    for(int i = 1; i < image.width()-1;i++){
        for(int j = 1; j < image.height()-1;j++){
            bool local_window[3][3] = {false};

            for(int m=-1;m<=1;m++){
                for(int n=-1;n<=1;n++){
                    QRgb rgbValue = image.pixel(i+m, j+n);
                    local_window[m+1][n+1] = (rgbValue != 0xffffffff);
                }
            }

            CustomMatrix mat(local_window);

            windows.push_back(mat);

            feature_type = "Background/Isolated Point"; // Default assumption

            if (mat.matches(SegmentPatterns::HORIZONTAL_LINE)) {
                feature_type = "Horizontal Line Segment";
            } else if (mat.matches(SegmentPatterns::VERTICAL_LINE)) {
                feature_type = "Vertical Line Segment";
            } else if (mat.matches(SegmentPatterns::CORNER_90)) {
                feature_type = "90-Degree Corner";
            } else if (mat.matches(SegmentPatterns::T_JUNCTION)) {
                feature_type = "T Junction";
            }

            cout << "CustomMatrix created at center coordinates: (" << i << ", " << j << ")" << endl;
        }
    }
    return;
}

void DrawingCanvas::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Set up the pen and brush for drawing the points
    QPen pen(Qt::blue, 5);
    painter.setPen(pen);
    painter.setBrush(QBrush(Qt::blue));

    // Draw a small circle at each stored point
    for (const QPoint& point : std::as_const(m_points)) {
        painter.drawEllipse(point, 3, 3);
    }

    if(isPaintLinesClicked){
        cout << "paint lines block is called" << endl;
        pen.setColor(Qt::red);
        pen.setWidth(4); // 4-pixel wide line
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);

        // Set the painter's pen to our custom pen.
        painter.setPen(pen);

        for(int i=0;i<m_points.size()-1;i+=2){
            //cout << m_points[i].x() << endl;
            painter.drawLine(m_points[i], m_points[i+1]);
        }
        isPaintLinesClicked = false;

        //return painter pen to blue
        pen.setColor(Qt::blue);
        painter.setPen(pen);
    }
}

void DrawingCanvas::mousePressEvent(QMouseEvent *event) {
    // Add the mouse click position to our vector of points
    m_points.append(event->pos());
    // Trigger a repaint
    update();
}




