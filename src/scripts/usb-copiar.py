import os
import shutil
import subprocess as sp
from pyudev import Context, Monitor



def auto_mount(path):
	args = ["sudo","udisksctl", "mount", "-b",path,"--no-user-interaction"]
	sp.run(args)
#end def

def get_mount_point(path):
	args = ["findmnt", "-unl", "-S", path]
	cp = sp.run(args, capture_output=True, text=True)
	out = cp.stdout.split(" ")[0]
	return out
#end def

def run_shell_script(script_path):
    try:
        sp.run(["/bin/bash", script_path], check=True)
    except sp.CalledProcessError as e:
        print(f"Error al ejecutar el script {script_path}: {e}")

def copy_zip_files(src_folder, dest_folder):
    # Verifica si la carpeta de destino existe y créala si es necesario
    if not os.path.exists(dest_folder):
        os.makedirs(dest_folder)

    # Recorre los archivos en la carpeta de origen y copia los archivos .zip a la carpeta de destino
    args = ["sudo","chmod","777","-R","/media/root"]
    sp.run(args)
    sp.run(["/bin/bash", "/home/pi/scripts/copy-core.sh",src_folder,dest_folder], check=True)


def main():
    context = Context()
    monitor = Monitor.from_netlink(context)
    monitor.filter_by(subsystem='block',device_type='partition')
    monitor.start()
    try:
        for device in iter(monitor.poll, None):
            if device.action == 'add':
                sp.call("sudo mount -o remount,rw / ; sudo mount -o remount,rw /boot",shell=True)
                print(f"Dispositivo USB conectado: {device}")
                auto_mount("/dev/" + device.sys_name)
                
                # Obtén la ruta de la raíz del dispositivo USB
                usb_root_path = get_mount_point("/dev/" + device.sys_name)
                
                # Especifica la carpeta de destino para los archivos .zip
                destination_folder = "/home/pi/.mame/roms/"

                # Ejecuta el primer script sh antes de copiar los archivos
                run_shell_script("/home/pi/scripts/mame-pause.sh")

                # Copia los archivos .zip de la raíz del dispositivo USB a la carpeta de destino
                copy_zip_files(usb_root_path, destination_folder)

                # Ejecuta el segundo script sh después de copiar los archivos
                run_shell_script("/home/pi/scripts/mame-resume.sh")
                sp.call("sudo mount -o remount,ro / ; sudo mount -o remount,ro /boot",shell=True)

            elif device.action == 'remove':
                print(f"Dispositivo USB desconectado: {device}")
    finally:
        pass

if __name__ == "__main__":
    main()

