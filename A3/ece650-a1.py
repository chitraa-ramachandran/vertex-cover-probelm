import sys
import re
import ast
from decimal import Decimal

street_details = dict()
flag = True

vertex_list_of_each_street = list()
vertices_plus_intersecting_points = list()
final_vertex_collection = dict()
collection_of_intersection_points = list()
vertices_pair_intersectioncheck = list()
remaining_list = list()

def vertex_format_string(x,y):
    vertex_str="(" + str(x) + "," + str(y) + ")"
    return vertex_str

def edge_format_string(p,q):
    edge_str="<" + str(p) + "," + str(q) + ">"
    return edge_str

def normalize_points(val):
    val = float(val)
    val = round(val, 2)
    return val

def street_checkvalidation(street_desc):
    if all(a.isalpha() or a.isspace() for a in street_desc):
        return True
    else:
        return False

def street_checkexist(street_desc):
    if street_desc in street_details:
        return True
    else:
        return False

def streetname_addition(street_desc):
    if street_desc not in street_details:
        return True
    else:
        return False

def points_check(location_desc):
    balance = []
    balance_check = True
    a = 0
    while a < len(location_desc) and balance_check:
        check_char = location_desc[a]
        if check_char == "(":
            balance.append(check_char)
        elif check_char == ")":
            if len(balance) == 0:
                balance_check = False
            else:
                balance.pop()
        a += 1
    return balance_check and len(balance) == 0

def points_validation(location_desc):
    regexp = r'\(-?\d+,-?\d+\)'
    corrected_exp = re.compile(regexp)
    if (corrected_exp.match(location_desc)):
        return True
    else:
        return False

def vertex_cover(new_vertex,vertices_pair,intersections):
    collection_of_intersection_points.append(new_vertex)
    vertices_pair_intersectioncheck.append(vertices_pair)
    intersections.append(new_vertex)
    graph_set = set(intersections)
    vertices_plus_intersecting_points = list(graph_set)
    for z in range(0, len(vertices_plus_intersecting_points)):
        final_vertex_collection[z] = vertices_plus_intersecting_points[z]

def graph_printer():

    final_edge_collection = list()
    unique_edge_collection = set()
    graph_set = set()
    direct_duplicate_edges = list()
    indirect_duplicate_edges = list()
    list_of_street_details = list(street_details.values())
    no_of_streets = len(list_of_street_details)
    vertex_list_of_each_street = [None] * no_of_streets
    iter1,iter2=1,1
    for a in range(0, no_of_streets):
        remaining_list = [i.split(', ', 1)[0] for i in list_of_street_details[a]]
        vertex_list_of_each_street[a] = remaining_list
    for i in range(0, no_of_streets):
        no_of_street1_vertices = len(vertex_list_of_each_street[i])
        for j in range(i + 1, no_of_streets):
            no_of_street2_vertices = len(vertex_list_of_each_street[j])
            while iter1 < no_of_street1_vertices:
                while iter2 < no_of_street2_vertices:
                    p1 = vertex_list_of_each_street[i][iter1 - 1]
                    p2 = vertex_list_of_each_street[i][iter1]
                    p3 = vertex_list_of_each_street[j][iter2 - 1]
                    p4 = vertex_list_of_each_street[j][iter2]
                    x1, y1 = ast.literal_eval(p1)
                    x2, y2 = ast.literal_eval(p2)
                    x3, y3 = ast.literal_eval(p3)
                    x4, y4 = ast.literal_eval(p4)
                    x1 = normalize_points(x1)
                    x2 = normalize_points(x2)
                    x3 = normalize_points(x3)
                    x4 = normalize_points(x4)
                    y1 = normalize_points(y1)
                    y2 = normalize_points(y2)
                    y3 = normalize_points(y3)
                    y4 = normalize_points(y4)
                    a1 = y2 - y1
                    a2 = y4 - y3
                    b1 = x1 - x2
                    b2 = x3 - x4
                    c1 = a1 * x1 + b1 * y1
                    c2 = a2 * x3 + b2 * y3
                    det = a1 * b2 - a2 * b1
                    min_x1 = min(x1, x2);
                    min_x2 = min(x3, x4);
                    max_x1 = max(x1, x2);
                    max_x2 = max(x3, x4);
                    min_y1 = min(y1, y2);
                    min_y2 = min(y3, y4);
                    max_y1 = max(y1, y2);
                    max_y2 = max(y3, y4);
                    flag1,flag2 = False,False
                    p1 = vertex_format_string(x1,y1)
                    p2 = vertex_format_string(x2,y2)
                    p3 = vertex_format_string(x3,y3)
                    p4 = vertex_format_string(x4,y4)
                    pair_list_considered = list((p1, p2, p3, p4))
                    if (det != 0):
                        X = Decimal((b2 * c1 - b1 * c2) / det)
                        Y = Decimal((a1 * c2 - a2 * c1) / det)
                        X = round(X, 2)
                        Y = round(Y, 2)
                        if (bool(X <= max_x1) & bool(X >= min_x1)):
                            if (bool(Y <= max_y1) & bool(Y >= min_y1)):
                                flag1 = True
                            if (bool(X <= max_x2) & bool(X >= min_x2)):
                                if (bool(Y <= max_y2) & bool(Y >= min_y2)):
                                    flag2 = True
                        if (flag1 == flag2==True):
                            new_vertex = vertex_format_string(X,Y)
                            vertices_plus_intersecting_points.extend(pair_list_considered)
                            vertex_cover(new_vertex,pair_list_considered,vertices_plus_intersecting_points)
                        else:
                            pass
                    elif (p1 == p4):
                        new_vertex = vertex_format_string(x4,y4)
                        vertices_plus_intersecting_points.extend(pair_list_considered)
                        vertex_cover(new_vertex,pair_list_considered,vertices_plus_intersecting_points)
                    elif (p2 == p3):
                        new_vertex = vertex_format_string(x3,y3)
                        vertices_plus_intersecting_points.extend(pair_list_considered)
                        vertex_cover(new_vertex, pair_list_considered, vertices_plus_intersecting_points)
                    elif (y1 == y2 == y3 == y4):
                        x_range1 = abs(x2 - x1)
                        x_range2 = abs(x4 - x3)
                        if (x_range1 > x_range2):
                            over_lapping = 1
                        elif (x_range2 > x_range1):
                            over_lapping = 2
                        if (over_lapping == 1):
                            if (x3 > min_x1 and x3 < max_x1):
                                new_vertex =vertex_format_string(x3,y3)
                                vertices_plus_intersecting_points.extend(pair_list_considered)
                                vertex_cover(new_vertex, pair_list_considered, vertices_plus_intersecting_points)
                            if (x4 > min_x1 and x4 < max_x1):
                                new_vertex = vertex_format_string(x4,y4)
                                vertices_plus_intersecting_points.extend(pair_list_considered)
                                vertex_cover(new_vertex, pair_list_considered, vertices_plus_intersecting_points)
                        if (over_lapping == 2):
                            if (x1 > min_x2 and x1 < max_x2):
                                new_vertex = vertex_format_string(x1,y1)
                                vertices_plus_intersecting_points.extend(pair_list_considered)
                                vertex_cover(new_vertex, pair_list_considered, vertices_plus_intersecting_points)
                            if (x2 > min_x2 and x2 < max_x2):
                                new_vertex = vertex_format_string(x2,y2)
                                vertices_plus_intersecting_points.extend(pair_list_considered)
                                vertex_cover(new_vertex, pair_list_considered, vertices_plus_intersecting_points)
                    elif (x1 == x2 == x3 == x4):
                        y_range1 = abs(y2 - y1)
                        y_range2 = abs(y4 - y3)
                        if (y_range1 > y_range2):
                            over_lapping = 1
                        elif (y_range2 > y_range1):
                            over_lapping = 2
                        if (over_lapping == 1):
                            if (y3 > min_y1 and y3 < max_y1):
                                new_vertex = vertex_format_string(x3,y3)
                                vertices_plus_intersecting_points.extend(pair_list_considered)
                                vertex_cover(new_vertex, pair_list_considered, vertices_plus_intersecting_points)
                            if (y4 > min_y1 and y4 < max_y1):
                                new_vertex = vertex_format_string(x4,y4)
                                vertices_plus_intersecting_points.extend(pair_list_considered)
                                vertex_cover(new_vertex, pair_list_considered, vertices_plus_intersecting_points)
                        if (over_lapping == 2):
                            if (y1 > min_y2 and y1 < max_y2):
                                new_vertex = vertex_format_string(x1,y1)
                                vertices_plus_intersecting_points.extend(pair_list_considered)
                                vertex_cover(new_vertex, pair_list_considered, vertices_plus_intersecting_points)
                            if (y2 > min_y2 and y2 < max_y2):
                                new_vertex = vertex_format_string(x2,y2)
                                vertices_plus_intersecting_points.extend(pair_list_considered)
                                vertex_cover(new_vertex, pair_list_considered, vertices_plus_intersecting_points)
                    iter2 = iter2 + 1
                iter1 = iter1 + 1
                iter2 = 1
            iter1 = 1
    sys.stdout.write("V ")
    sys.stdout.flush()
    sys.stdout.write(str(len(final_vertex_collection)) + '\n')
    sys.stdout.flush()
    for b in range(0, len(collection_of_intersection_points)):
        intersection_pt = collection_of_intersection_points[b]
        vertexlist = vertices_pair_intersectioncheck[b]
        [p1, p2, p3, p4] = vertexlist
        for c in final_vertex_collection:
            if intersection_pt == final_vertex_collection[c]:
                edge_start = c
        for identity, coords in final_vertex_collection.items():
            if coords == p1:
                edge_end1 = identity
        for identity, coords in final_vertex_collection.items():
            if coords == p2:
                edge_end2 = identity
        for identity, coords in final_vertex_collection.items():
            if coords == p3:
                edge_end3 = identity
        for identity, coords in final_vertex_collection.items():
            if coords == p4:
                edge_end4 = identity
        edge1 = edge_format_string(edge_start,edge_end1)
        edge2 = edge_format_string(edge_start,edge_end2)
        edge3 = edge_format_string(edge_start,edge_end3)
        edge4 = edge_format_string(edge_start,edge_end4)
        edgelist = list((edge1, edge2, edge3, edge4))
        final_edge_collection.extend(edgelist)
        unique_edge_collection = set(final_edge_collection)
        final_edge_collection = list(unique_edge_collection)
        distinct_new_vertices = list()
        for d in range(0, len(final_edge_collection)):
            pair = final_edge_collection[d]
            pair = re.sub('<', '(', pair)
            pair = re.sub('>', ')', pair)
            x_coord, y_coord = ast.literal_eval(pair)
            distinct_new_vertices.append(x_coord)
            distinct_set = set(distinct_new_vertices)
            distinct_new_vertices = list(distinct_set)
            for e in range(0, len(distinct_new_vertices)):
                for f in range(e + 1, len(distinct_new_vertices)):
                    edge_between = edge_format_string(str(distinct_new_vertices[e]),str(distinct_new_vertices[f]))
                    final_edge_collection.append(edge_between)
                    graph_set = set(final_edge_collection)
                    final_edge_collection = list(graph_set)
    for g in range(0, len(final_edge_collection)):
        edge_1 = final_edge_collection[g]
        edge_1 = re.sub('<', '(', edge_1)
        edge_1 = re.sub('>', ')', edge_1)
        p1, p2 = ast.literal_eval(edge_1)
        if (p1 == p2):
            delete = edge_format_string(p1,p2)
            direct_duplicate_edges.append(delete)
        for h in final_vertex_collection:
            v1 = final_vertex_collection[p1]
            v2 = final_vertex_collection[p2]
            v_x1, v_y1 = ast.literal_eval(v1)
            v_x2, v_y2 = ast.literal_eval(v2)
            min_x1 = min(v_x1, v_x2)
            max_x1 = max(v_x1, v_x2)
            min_y1 = min(v_y1, v_y2)
            max_y1 = max(v_y1, v_y2)
            check_v1_v2 = final_vertex_collection[h]
            c_x, c_y = ast.literal_eval(check_v1_v2)
            if (v1 not in collection_of_intersection_points) or (v2 not in collection_of_intersection_points):
             if ((bool(c_x != min_x1) & bool(c_x != max_x1)) | ((bool(c_y != min_y1) & bool(c_y != max_y1)))):
                if (bool(c_x <= max_x1) & bool(c_x >= min_x1)):
                    if (bool(c_y <= max_y1) & bool(c_y >= min_y1)):
                        del_duplicate = edge_format_string(p1,p2)
                        direct_duplicate_edges.append(del_duplicate)
                        direct_duplicate_edges_set = set(direct_duplicate_edges)
                        direct_duplicate_edges = list(direct_duplicate_edges_set)
    for l in range(0, len(final_edge_collection)):
        for l1 in range(l + 1, len(final_edge_collection)):
            edge_1 = final_edge_collection[l]
            edge_1 = re.sub('<', '(', edge_1)
            edge_1 = re.sub('>', ')', edge_1)
            p1, p2 = ast.literal_eval(edge_1)
            edge_2 = final_edge_collection[l1]
            edge_2 = re.sub('<', '(', edge_2)
            edge_2 = re.sub('>', ')', edge_2)
            p3, p4 = ast.literal_eval(edge_2)
            if (p1 == p4 and p2 == p3):
                delete = edge_format_string(p1,p2)
                indirect_duplicate_edges.append(delete)
                duplicate_edges_set1 = set(indirect_duplicate_edges)
                indirect_duplicate_edges = list(duplicate_edges_set1)
    for m in range(0, len(indirect_duplicate_edges)):
        final_edge_collection.remove(indirect_duplicate_edges[m])
    for k in range(0, len(direct_duplicate_edges)):
        final_edge_collection.remove(direct_duplicate_edges[k])
    sys.stdout.write("E {")
    sys.stdout.flush()
    count = len(final_edge_collection)
    for u in final_edge_collection:
        sys.stdout.flush()
        sys.stdout.write(u)
        sys.stdout.flush()
        count = count - 1
        if (count):
            sys.stdout.write(',')
            sys.stdout.flush()
    sys.stdout.write("}" + '\n')
    sys.stdout.flush()


def main():
    while (True):
        try:
         user_input = raw_input()
        except(EOFError):
          sys.stdout.flush()
          break
        if user_input == '':
            break
        elif user_input[0] == 'r':
            processed_input = re.split(' +"|"|', user_input)
        else:
            processed_input = re.split('" +| +"', user_input)
        if len(processed_input) == 3:
                option = processed_input[0]
                street_desc = processed_input[1]
                street_desc = street_desc.lower()
                location_desc = processed_input[2]
        elif len(processed_input) == 2:
                option = processed_input[0]
                street_desc = processed_input[1]
                street_desc = street_desc.lower()
        elif len(processed_input) == 1:
                option = processed_input[0]
        else:
            sys.stderr.write(
                "Error: " + "Wrong standard input.Kindly enter user_input in format: " + " command(a,c,r,g) \"street name\" street points" + '\n')
            sys.stdout.flush()
            continue

        if option == 'g':
            graph_printer()
            sys.stdout.flush()
        elif option == 'r':
            try:
                if(street_details.__contains__(street_desc)):
                    del street_details[street_desc]
                else:
                    sys.stderr.write(
                        "Error: " + street_desc + " doesn't exists in the dictionary or it might have been removed already!" + '\n')
                    sys.stdout.flush()
            except UnboundLocalError:
                sys.stderr.write(
                    "Error: " + "Invalid user input! The standard input format is :" + "r 'street name'" + '\n')
                sys.stdout.flush()
        elif option == 'c':
            try:
                if (street_checkexist(street_desc)):
                    if (street_checkvalidation(street_desc)):
                        if (points_check(location_desc)):
                            location_desc = re.sub(' +', '', location_desc)
                            location_desc = re.sub('\)\(', ') ( ', location_desc)
                            location_desc = re.sub('\( ', '(', location_desc)
                            location_desc = location_desc.split(' ')
                            if all(points_validation(i) for i in location_desc):
                                street_details[street_desc] = location_desc
                            else:
                                sys.stderr.write(
                                    "Error: " + "points of the street is not in proper format!(points can only be of integer type)" + '\n')
                                sys.stdout.flush()
                        else:
                            sys.stderr.write(
                                "Error: " + "Paranthesis in the points provided is not balanced! check on the paranthesis again." + '\n')
                            sys.stdout.flush()
                    else:
                        sys.stderr.write(
                            "Error: " + "Street name is invalid! Street name can have whitespace and alphabets only along with proper street points" + '\n')
                        sys.stdout.flush()
                else:
                    sys.stderr.write("Error: " + "Street name is not present or point input is not given! " + '\n')
                    sys.stdout.flush()
            except UnboundLocalError:
                sys.stderr.write(
                    "Error: " + "Invalid user input! The standard input format is :" + "c 'street name' points" + '\n')
                sys.stdout.flush()
        elif option == 'a':
            try:
                if (street_checkvalidation(street_desc)):
                    if (points_check(location_desc)):
                        if (streetname_addition(street_desc)):
                            location_desc = re.sub(' +', '', location_desc)
                            location_desc = re.sub('\)\(', ') ( ', location_desc)
                            location_desc = re.sub('\( ', '(', location_desc)
                            location_desc = location_desc.split(' ')
                            if all(points_validation(i) for i in location_desc):
                                street_details[street_desc] = location_desc
                            else:
                                sys.stderr.write(
                                    "Error: " + "points of the street is not in proper format!(points can only be of integer type)" + '\n')
                                sys.stdout.flush()
                        else:
                            sys.stderr.write("Error: " + "Street name is already present in the dictionary!" + '\n')
                            sys.stdout.flush()
                    else:
                        sys.stderr.write(
                            "Error: " + "Paranthesis in the points provided is not balanced! check on the paranthesis again." + '\n')
                        sys.stdout.flush()
                else:
                    sys.stderr.write(
                        "Error: " + "Street name is invalid! Street name can have whitespace and alphabets only along with proper street points" + '\n')
                    sys.stdout.flush()
            except UnboundLocalError:
                sys.stderr.write(
                    "Error: " + "Invalid user input! The standard input format is :" + "a 'street name' points" + '\n')
                sys.stdout.flush()
        else:
            sys.stderr.write("Error: " + "Invalid option!The options available are:a,c,r or g only!!" + '\n')
            sys.stdout.flush()
    sys.stdout.flush()

if __name__ == '__main__':
    main()
