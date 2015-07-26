sentence=raw_input("Sentence: ")

screen_width=80
text_width=len(sentence)
box_width=text_width+6
left_margin=(screen_width-box_width)//2

print
print ' '*left_margin+'+'+'-'*(box_width-2)+'+'
print ' '*(1+left_margin)+'| '+' '*text_width+' |'
print ' '*(1+left_margin)+'| '+sentence+' |'
print ' '*(1+left_margin)+'| '+' '*text_width+' |'
print ' '*left_margin+'+'+'-'*(box_width-2)+'+'
print
