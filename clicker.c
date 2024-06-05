#include <gtk/gtk.h>
#include <stdio.h>

#define CLICKS_FILE "clicks.txt"

static GtkWidget *label;
static int click_count = 0;

void load_click_count() {
    FILE *file = fopen(CLICKS_FILE, "r");
    if (file != NULL) {
        fscanf(file, "%d", &click_count);
        fclose(file);
    }
}

void save_click_count() {
    FILE *file = fopen(CLICKS_FILE, "w");
    if (file != NULL) {
        fprintf(file, "%d", click_count);
        fclose(file);
    }
}

void on_button_clicked(GtkWidget *widget, gpointer data) {
    click_count++;
    char count_str[50];
    sprintf(count_str, "<big><b>Количество кликов: %d</b></big>", click_count);
    gtk_label_set_markup(GTK_LABEL(label), count_str);
    save_click_count();
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *grid;

    gtk_init(&argc, &argv);

    load_click_count();

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Кликер");
    gtk_window_set_default_size(GTK_WINDOW(window), 125, 250); // Размер окна 125x250
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    label = gtk_label_new("");
    char count_str[50];
    sprintf(count_str, "<big><b>Количество кликов: %d</b></big>", click_count);
    gtk_label_set_markup(GTK_LABEL(label), count_str);
    gtk_grid_attach(GTK_GRID(grid), label, 0, 1, 1, 1);

    button = gtk_button_new_with_label("Кликни меня!");
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 2, 1, 1);

    gtk_widget_set_margin_top(label, 20);
    gtk_widget_set_hexpand(button, TRUE);
    gtk_widget_set_halign(button, GTK_ALIGN_CENTER);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
