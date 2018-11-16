#! /bin/bash

#Get creation timestamp of a file

get_creation_time() {
    inode=$(stat -c '%i' "$1")
    fs=$(df --output=source "$1" | tail -1)
    creation_time=$(sudo debugfs -R 'stat <'"${inode}"'>' "${fs}" 2>/dev/null | 
    grep -oP 'crtime.*--\s*\K.*')
    printf "%s" "${creation_time}"
}

#Put directory entries into array

entries=()

for entry in "$1"/* do
    entries+=("$entry")
done

#Sort direcotry entries by name

IFS=$'\n' entries=($(sort -r <<<"${entries[*]}"))
unset IFS

#Split directory entries into files and directories

directories=()
files=()

for entry in "${entries[@]}" do
    base_name=$(basename "$entry")
    if [[ -d $entry ]]; then
        directories+=("$base_name") 
    elif [[ -f $entry ]]; then
        creation_date=$(get_creation_time $entry)
        hard_links_number=$(stat --format="%h" "$entry")
        file_length=$(stat --format="%s" "$entry")
        files+=("$base_name || created at $creation_date || links number is $hard_links_number || length is $file_length")
    fi
done

#Output directory entries

for directory in "${directories[@]}" do
    echo "$directory" 
done

for file in "${files[@]}" do
    echo "$file" 
done






