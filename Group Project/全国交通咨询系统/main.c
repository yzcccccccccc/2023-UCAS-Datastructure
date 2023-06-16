#include<gtk/gtk.h>
#include<stdio.h>
#include"system_core.h"

#define MAX_BUFF_SIZE 1000

GtkBuilder *builder;
GtkWidget *window;

void RouteShow(int status){
    GtkWidget *RouteAns_text = GTK_WIDGET(gtk_builder_get_object(builder, "Route_Ans"));
    GtkTextBuffer *text_buff = gtk_text_view_get_buffer(GTK_TEXT_VIEW(RouteAns_text));

    GtkTextIter start, end;
    gtk_text_buffer_get_bounds(text_buff, &start, &end);
    gtk_text_buffer_delete(text_buff, &start, &end);

    gchar buff[MAX_BUFF_SIZE];
    if (status != 0){
        sprintf(buff, "%s", "No Route Available");
        gtk_text_buffer_get_end_iter(text_buff, &end);
        gtk_text_buffer_insert(text_buff, &end, buff, -1);
    }
    else{
        sprintf(buff, "%10s%6s%10s%10s%10s%10s%7s\n", 
                "Tra_type",
                "ID",
                "Dep_city",
                "Arr_city",
                "Dep_time",
                "Arr_time",
                "Price"
                );
        gtk_text_buffer_get_end_iter(text_buff, &end);
        gtk_text_buffer_insert(text_buff, &end, buff, -1);
        char Type[MAXLEN] = "Flight";
        if (Route_Ans[0].type == TRAIN_MARK)
            strcpy(Type, "Train");

        char dep_time[MAXLEN], arr_time[MAXLEN];

        //printf("Ans_Len%d\n", Ans_Len);
        for (int i = 0; i < Ans_Len; i++){
            sprintf(dep_time, "%02d:%02d", Route_Ans[i].dep_time / 60, Route_Ans[i].dep_time % 60);
            sprintf(arr_time, "%02d:%02d", Route_Ans[i].arr_time / 60, Route_Ans[i].arr_time % 60);
            sprintf(buff, "%10s%6s%10s%10s%10s%10s%7d\n", 
                Type,
                Route_Ans[i].id,
                GPH.city_list[Route_Ans[i].u], GPH.city_list[Route_Ans[i].v],  
                dep_time, arr_time, Route_Ans[i].price);
            gtk_text_buffer_get_end_iter(text_buff, &end);
            gtk_text_buffer_insert(text_buff, &end, buff, -1);
            //printf("%s", buff);
        }
        sprintf(buff, "%d Yuan, %02dh %02dm, +%d %s, change %d %s\n", 
            Ans_cost, Ans_time / 60, Ans_time % 60, Ans_Day, (Ans_Day > 1) ? "days" : "day", Ans_change, (Ans_change > 1) ? "times" : "time");
        gtk_text_buffer_get_end_iter(text_buff, &end);
        gtk_text_buffer_insert(text_buff, &end, buff, -1);
        //printf("%s", buff);
    }
    
    return;
}

void ShowInfoWin(char *info){
    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            "%s",
            (gchar *)info);
    gtk_window_set_title(GTK_WINDOW(dialog), "Information");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

G_MODULE_EXPORT void View_but_clicked_cb(GtkWidget *widget, GdkEvent *event, gpointer user_data){
    system("clear");
    Print_graph(GPH);
}

// Query func
G_MODULE_EXPORT void Query_but_clicked_cb(GtkWidget *widget, GdkEvent *event, gpointer user_data){
    GtkWidget *dep_entry, *arr_entry;
    dep_entry = GTK_WIDGET(gtk_builder_get_object(builder, "Departure_box"));
    arr_entry = GTK_WIDGET(gtk_builder_get_object(builder, "Arrival_box"));

    const gchar *g_dep_city, *g_arr_city;
    g_dep_city = gtk_entry_get_text(GTK_ENTRY(dep_entry));
    g_arr_city = gtk_entry_get_text(GTK_ENTRY(arr_entry));

    char dep_city[City_MAXLEN], arr_city[City_MAXLEN];
    sprintf(dep_city, "%s", g_dep_city);
    sprintf(arr_city, "%s", g_arr_city);
    //printf("%s %s\n", dep_city, arr_city);

    GtkWidget *tra_combo, *req_combo;
    tra_combo = GTK_WIDGET(gtk_builder_get_object(builder, "tra_option_combo"));
    req_combo = GTK_WIDGET(gtk_builder_get_object(builder, "req_option_combo"));

    char tra_mode[MAXLEN], tra_req[MAXLEN];
    sprintf(tra_mode, "%s", gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(tra_combo)));
    sprintf(tra_req, "%s", gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(req_combo)));
    //printf("%s %s\n", tra_mode, tra_req);

    #ifndef DIJKSTRA
        int status = DFS(dep_city, arr_city, 
                tra_mode[0] == 'T' ? TRAIN_MARK : FLIGHT_MARK, 
                tra_req[0] == 'T' ? TIME_FIRST :  (tra_req[1] == 'O' ? COST_FIRST : INTERCHANGE_FIRST));
    #else
        
    #endif
    RouteShow(status);
    //printf("Query done\n");
    return;
}

G_MODULE_EXPORT void Load_File_but_clicked_cb(GtkWidget *widget, GdkEvent *event, gpointer user_data){
    int status = LoadFile();
    char dia_info[Info_MAXLEN];
    if (status == 0)
        sprintf(dia_info, "Successfully load file\n");
    else
        sprintf(dia_info, "File error\n");
    ShowInfoWin(dia_info);
}

RouteInfo GetTrainFlightInfo(){
    RouteInfo info;
    GtkWidget *dep_city_entry, *arr_city_entry, *dep_time_entry, *arr_time_entry;
    GtkWidget *id_entry, *price_entry;

    dep_city_entry = GTK_WIDGET(gtk_builder_get_object(builder, "edit_src_city_box"));
    arr_city_entry = GTK_WIDGET(gtk_builder_get_object(builder, "edit_dest_city_box"));
    dep_time_entry = GTK_WIDGET(gtk_builder_get_object(builder, "edit_dep_time_box"));
    arr_time_entry = GTK_WIDGET(gtk_builder_get_object(builder, "edit_arr_time_box"));
    id_entry = GTK_WIDGET(gtk_builder_get_object(builder, "edit_id_box"));
    price_entry = GTK_WIDGET(gtk_builder_get_object(builder, "edit_price_box"));

    sscanf(gtk_entry_get_text(GTK_ENTRY(dep_city_entry)), "%s", info.dep_city);
    sscanf(gtk_entry_get_text(GTK_ENTRY(arr_city_entry)), "%s", info.arr_city);
    sscanf(gtk_entry_get_text(GTK_ENTRY(id_entry)), "%s", info.id);
    info.dep_time = TimeConvert(gtk_entry_get_text(GTK_ENTRY(dep_time_entry)));
    info.arr_time = TimeConvert(gtk_entry_get_text(GTK_ENTRY(arr_time_entry)));
    sscanf(gtk_entry_get_text(GTK_ENTRY(price_entry)), "%d", &info.price);
    return info;
}

G_MODULE_EXPORT void add_Train_but_clicked_cb(GtkWidget *widget, GdkEvent *event, gpointer user_data){
    RouteInfo info = GetTrainFlightInfo();
    info.mode = TRAIN_MARK;
    int status = Add_Route(info);
    char dia_info[Info_MAXLEN];
    if (status == 0)
        sprintf(dia_info, "Successfully add Train");
    else{
        sprintf(dia_info, "%s_city not found\n", (status == DEP_CITY_NOT_IN) ? "dep" : "arr");
    }
    ShowInfoWin(dia_info);
}

G_MODULE_EXPORT void del_Train_but_clicked_cb(GtkWidget *widget, GdkEvent *event, gpointer user_data){
    RouteInfo info = GetTrainFlightInfo();
    info.mode = TRAIN_MARK;
    int status = Del_Route(info);
    char dia_info[Info_MAXLEN];
    if (status == 0)
        sprintf(dia_info, "Successfully dels Train\n");
    else{
        sprintf(dia_info, "Route not in the system\n");
    }
    ShowInfoWin(dia_info);
}

G_MODULE_EXPORT void add_Flight_but_clicked_cb(GtkWidget *widget, GdkEvent *event, gpointer user_data){
    RouteInfo info = GetTrainFlightInfo();
    info.mode = FLIGHT_MARK;
    int status = Add_Route(info);
    char dia_info[Info_MAXLEN];
    if (status == 0)
        sprintf(dia_info, "Successfully add Flight\n");
    else{
        sprintf(dia_info, "%s_city not found\n", (status == DEP_CITY_NOT_IN) ? "dep" : "arr");
    }
    ShowInfoWin(dia_info);
}

G_MODULE_EXPORT void del_Flight_but_clicked_cb(GtkWidget *widget, GdkEvent *event, gpointer user_data){
    RouteInfo info = GetTrainFlightInfo();
    info.mode = FLIGHT_MARK;
    int status = Del_Route(info);
    char dia_info[Info_MAXLEN];
    if (status == 0)
        sprintf(dia_info, "Successfully del Flight\n");
    else{
        sprintf(dia_info, "Route not in the system\n");
    }
    ShowInfoWin(dia_info);
}

G_MODULE_EXPORT void add_city_but_clicked_cb(GtkWidget *widget, GdkEvent *event, gpointer user_data){
    GtkWidget *city_name_entry = GTK_WIDGET(gtk_builder_get_object(builder, "city_box"));
    char city_name[City_MAXLEN];
    sprintf(city_name, "%s", gtk_entry_get_text(GTK_ENTRY(city_name_entry)));
    int status = Add_City(city_name);

    char dia_info[Info_MAXLEN];
    if (status == 0)
        sprintf(dia_info, "Successfully add city %s\n", city_name);
    else{
        sprintf(dia_info, "City already in the list\n");
    }
    ShowInfoWin(dia_info);
}

G_MODULE_EXPORT void del_city_but_clicked_cb(GtkWidget *widget, GdkEvent *event, gpointer user_data){
    GtkWidget *city_name_entry = GTK_WIDGET(gtk_builder_get_object(builder, "city_box"));
    char city_name[City_MAXLEN];
    sprintf(city_name, "%s", gtk_entry_get_text(GTK_ENTRY(city_name_entry)));
    int status = Del_City(city_name);
    char dia_info[Info_MAXLEN];
    if (status == 0)
        sprintf(dia_info, "Successfully del city %s\n", city_name);
    else{
        sprintf(dia_info, "City not in the list\n");
    }
    ShowInfoWin(dia_info);
}

G_MODULE_EXPORT void TopWindow_destroy_cb(GtkWidget *widget, GdkEvent *event, gpointer user_data){
    gtk_main_quit();
}

int main(int argc, char *argv[]){
    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    if (!gtk_builder_add_from_file(builder, "./GUI.glade", NULL)){
        printf("Cannot Load GUI file.");
    }

    window = GTK_WIDGET(gtk_builder_get_object(builder, "TopWindow"));

    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}