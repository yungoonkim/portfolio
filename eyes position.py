import cv2 as cv
import numpy as np
import mediapipe as mp
import math

mp_face_mesh = mp.solutions.face_mesh

LEFT_EYE=[ 
    362, 382, 381, 380, 374, 373, 390, 249, 263, 
    466, 388, 387, 386, 385, 384, 398 
            ] 
RIGHT_EYE=[ 
    33, 7, 163, 144, 145, 153, 154, 155, 133,
    173, 157, 158, 159, 160, 161 , 246 
            ]  
RIGHT_IRIS=[ 474, 475, 476, 477 ]
LEFT_IRIS=[ 469, 470, 471, 472 ]
L_H_LEFT = [33]
L_H_RIGHT = [133]
R_H_LEFT = [362]
R_H_RIGHT = [263]


def euclidean_distance(point1, point2):
    x1, y1 = point1.ravel()
    x2, y2 = point2.ravel()
    distance = math.sqrt((x2-x1)**2 + (y2-y1)**2)
    return distance
def iris_position(iris_center, right_point, left_point):
    center_to_right_dist = euclidean_distance(iris_center, right_point)
    total_distance = euclidean_distance(right_point, left_point)
    ratio = center_to_right_dist/total_distance
    iris_position = ""
    if ratio<=0.45:
        iris_position="right"
    elif ratio>0.45 and ratio<=0.57:
        iris_position="center"
    else:
        iris_position="left"
    return iris_position, ratio

cap = cv.VideoCapture(0)
with mp_face_mesh.FaceMesh(
    max_num_faces=1, 
    refine_landmarks=True, 
    min_detection_confidence=0.5,
    min_tracking_confidence=0.5
) as face_mesh:
    while True:
        ret, frame = cap.read()
        if not ret:
            break
        frame = cv.flip(frame, 1)
        rgb_frame = cv.cvtColor(frame, cv.COLOR_BGR2RGB)
        img_h, img_w = frame.shape[:2]
        results = face_mesh.process(rgb_frame)
        if results.multi_face_landmarks:
            #print(results.multi_face_landmarks[0].landmark)
            mesh_points=np.array([np.multiply([p.x, p.y], [img_w, img_h]).astype(int) for p in results.multi_face_landmarks[0].landmark])
            #print(mesh_points.shape)
            #cv.polylines(frame, [mesh_points[LEFT_IRIS]], True, (0,255,0), 1, cv.LINE_AA)
            #cv.polylines(frame, [mesh_points[RIGHT_IRIS]], True, (0,255,0), 1, cv.LINE_AA)
            (l_cx, l_cy), l_radius = cv.minEnclosingCircle(mesh_points[LEFT_IRIS])
            (r_cx, r_cy), r_radius = cv.minEnclosingCircle(mesh_points[RIGHT_IRIS])
            center_left = np.array([l_cx, l_cy], dtype=np.int32)
            center_right = np.array([r_cx, r_cy], dtype=np.int32)
            cv.circle(frame, center_left, int(l_radius), (0,255,0), 1, cv.LINE_AA)
            cv.circle(frame, center_right, int(r_radius), (0,255,0), 1, cv.LINE_AA)
            cv.circle(frame, mesh_points[R_H_RIGHT][0], 3, (255,255,255), -1, cv.LINE_AA)
            cv.circle(frame, mesh_points[R_H_LEFT][0], 3, (0,255,255), -1, cv.LINE_AA)
            cv.circle(frame, mesh_points[L_H_RIGHT][0], 3, (255,255,255), -1, cv.LINE_AA)
            cv.circle(frame, mesh_points[L_H_LEFT][0], 3, (0,0,0), -1, cv.LINE_AA)
            iris_pos, ratio=iris_position(
                center_right, mesh_points[R_H_RIGHT], mesh_points[R_H_LEFT][0]
                )
            #print(iris_pos)
            cv.putText(frame, f"Iris pos: {iris_pos} {ratio:.2f}",  (30,30), cv.FONT_HERSHEY_PLAIN, 1.2, (0,255,0), 1, cv.LINE_AA)
            
            
       
        cv.imshow('img',frame)
        key = cv.waitKey(1)
        if key == ord('q'):
            break
cap.release()
cv.destroyAllWindows()
